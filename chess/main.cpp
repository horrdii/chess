#include "classes/field.h"

RenderWindow window;
field f;

int main() {

	RenderWindow window(VideoMode(800, 800), "Collision");
	Event event;

	Sprite s;
	Texture t;

	CircleShape mark;
	mark.setFillColor(Color::White);
	mark.setRadius(20);

	RectangleShape tile;
	tile.setSize(Vector2f(100, 100));
	tile.setOutlineColor(Color::Black);
	tile.setOutlineThickness(3);

	Font font;
	font.loadFromFile("sprites/Goose.ttf");

	Text wonText;
	wonText.setCharacterSize(100);
	wonText.setFillColor(Color::Red);
	wonText.setFont(font);

	float time = 0;

	FloatRect wonTexRect = wonText.getGlobalBounds();
	/*wonText.setOrigin(wonTexRect.left + wonTexRect.width/2.f,
					wonTexRect.top + wonTexRect.height/2.f);*/
	wonText.setPosition(160, 330);

	while (window.isOpen())
	{
		while (window.pollEvent(event)) {
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::MouseButtonPressed:
				if(f.win == NULL)
					f.check(Mouse::getPosition(window));
				break;
			}
		}

		window.clear();


		auto v = f.f;
		for (int i = 0; i < v.size(); i++) {

			for (int j = 0; j < v.size(); j++) {

				tile.setFillColor(i % 2 == 0 ? j % 2 == 0 ? Color::Yellow : Color::Cyan : j % 2 == 0 ? Color::Cyan : Color::Yellow);
				tile.setPosition(j * 100, i * 100);
				window.draw(tile);

				if (v[i][j] == "")
					continue;

				t.loadFromImage(f.figures[v[i][j][1]][v[i][j][0]]);
				s.setTexture(t);
				s.setScale(1, 1);
				s.setPosition(j * 100+17, i * 100+17);
				window.draw(s);
			}
		}

		for (pair<int, int> i : f.getMarkedTiles()) {
			mark.setPosition(i.second * 100 + 30, i.first * 100 + 30);
			window.draw(mark);
		}

		if (f.win != NULL) {
			wonText.setString(f.win == 'w' ? "White won" : "Black won");
			window.draw(wonText);
			time += 0.01;
			if(time > 3)
				exit(42);
		}

		window.display();

	}
}