#include "field.h"


field::field() {
	Image BPawn, WPawn;
	Image BBishop, WBishop;
	Image BKing, WKing;
	Image BHorse, WHorse;
	Image BRook, WRook;
	Image BQueen, WQueen;

	BPawn.loadFromFile("sprites/BPawn.png");
	WPawn.loadFromFile("sprites/WPawn.png");
	BBishop.loadFromFile("sprites/BBishop.png");
	WBishop.loadFromFile("sprites/WBishop.png");
	BKing.loadFromFile("sprites/BKing.png");
	WKing.loadFromFile("sprites/WKing.png");
	BHorse.loadFromFile("sprites/BHorse.png");
	WHorse.loadFromFile("sprites/WHorse.png");
	BRook.loadFromFile("sprites/BRook.png");
	WRook.loadFromFile("sprites/WRook.png");
	BQueen.loadFromFile("sprites/BQueen.png");
	WQueen.loadFromFile("sprites/WQueen.png");

	figures['p'] = { {'b', BPawn}, {'w', WPawn} };
	figures['b'] = { {'b', BBishop}, {'w', WBishop}};
	figures['k'] = { {'b', BKing}, {'w', WKing} };
	figures['h'] = { {'b', BHorse}, {'w', WHorse} };
	figures['r'] = { {'b', BRook}, {'w', WRook} };
	figures['q'] = { {'b', BQueen}, {'w', WQueen} };

	f = { {"br", "bh", "bb", "bq", "bk", "bb", "bh", "br"},
		{"bp", "bp", "bp", "bp", "bp", "bp", "bp", "bp"},
		{"", "", "", "", "", "", "", ""}, 
		{"", "", "", "", "", "", "", ""},
		{"", "", "", "", "", "", "", ""},
		{"", "", "", "", "", "", "", ""},
		{"wp", "wp", "wp", "wp", "wp", "wp", "wp", "wp"},
		{"wr", "wh", "wb", "wq", "wk", "wb", "wh", "wr"} };
}


void field::check(Vector2i mousePos) {
	int y = (mousePos.y / 100), x = (mousePos.x / 100);
	string tile = f[y][x];

	if (y == checkFigY && x == checkFigX && markedTiles.size() > 0) {
		clearMarks();
		return;
	}


	for (const pair<int, int>& i : markedTiles) {
		if (i.first == y && i.second == x) {
			clearMarks();

			if (f[y][x].length() > 0 && f[y][x][1] == 'k')
				win = checkColor;

			checkColor = checkColor == 'w' ? 'b' : 'w';
			f[y][x] = f[checkFigY][checkFigX];
			f[checkFigY][checkFigX] = "";
			return;
		}
	}

	marking(tile, x, y);

}


void field::marking(string tile, int x, int y) {
	if (tile == "" || tile[0] != checkColor)
		return;
	clearMarks();

	switchMarks(markedTiles, tile, x, y);

	checkFigX = x;
	checkFigY = y;

}


void field::switchMarks(vector<pair<int ,int>> &v, string tile, int x, int y) {
	switch (tile[1]) {
	case 'p':

		pawnMarks(v, tile, y, x);

		break;


	case 'b':

		diagonalMarks(v, tile, y, x);

		break;


	case 'r':

		horizontalMarks(v, tile, y, x);

		break;


	case 'q':

		diagonalMarks(v, tile, y, x);
		horizontalMarks(v, tile, y, x);

		break;


	case 'h':

		horseMarks(v, tile, y, x);

		break;


	case 'k':

		kingMarks(v, tile, y, x);

		break;

	}
}


void field::clearMarks() {
	markedTiles.clear();
}


vector<pair<int, int>> field::getMarkedTiles() {
	return markedTiles;
}



void field::pawnMarks(vector<pair<int, int>>& v, string tile, int y, int x) {
	if (tile[0] == 'b') {

		if (y + 1 < 8) {

			if (f[y + 1][x].length() == 0)
				markedTiles.push_back({ y + 1, x });
			if (x + 1 < 8 && f[y + 1][x + 1][0] == 'w')
				markedTiles.push_back({ y + 1 , x + 1 });
			if (x - 1 > -1 && f[y + 1][x - 1][0] == 'w')
				markedTiles.push_back({ y + 1, x - 1 });

		}
	}
	else {
		if (y - 1 > -1) {
			if (f[y - 1][x].length() == 0)
				markedTiles.push_back({ y - 1, x });
			if (x + 1 < 8 && f[y - 1][x + 1][0] == 'b')
				markedTiles.push_back({ y - 1 , x + 1 });
			if (x - 1 > -1 && f[y - 1][x - 1][0] == 'b')
				markedTiles.push_back({ y - 1, x - 1 });
		}
	}
}

void field::kingMarks(vector<pair<int, int>>& v, string tile, int y, int x) {
	vector<pair<int, int>> tiles{
		{y + 1, x}, {y + 1, x + 1}, {y, x + 1}, {y-1, x}, {y-1, x-1}, {y, x-1}, {y+1, x-1}, {y-1, x+1}
	};

	for (const auto& i : tiles) {
		if (i.first > -1 && i.first < 8 && i.second > -1 && i.second < 8 && (f[i.first][i.second] == "" || f[i.first][i.second][0] != tile[0]))
			v.push_back({ i.first, i.second });
	}
}

void field::horseMarks(vector<pair<int, int>>& v, string tile, int y, int x) {
	vector<pair<int, int>> tiles{
		{y+2, x-1}, {y+2, x+1}, {y-2, x-1}, {y-2, x+1}, {y+1, x-2}, {y-1, x-2}, {y+1, x+2}, {y-1, x+2}
	};

	for (const auto& i : tiles) {
		if (i.first > -1 && i.first < 8 && i.second > -1 && i.second < 8 && (f[i.first][i.second] == "" || f[i.first][i.second][0] != tile[0]))
			v.push_back({i.first, i.second});
	}
}

void field::horizontalMarks(vector<pair<int, int>>& v, string tile, int y, int x) {
	int i = 1;
	while (x + i < 8 && f[y][x + i][0] != tile[0]) {
		v.push_back({ y, x + i });
		if (f[y][x + i] != "")
			break;
		i++;
	}
	i = 1;

	while (x - i > -1 && f[y][x - i][0] != tile[0]) {
		v.push_back({ y, x - i });
		if (f[y][x - i] != "")
			break;
		i++;
	}
	i = 1;

	while (y + i < 8 && f[y + i][x][0] != tile[0]) {
		v.push_back({ y + i, x });
		if (f[y + i][x] != "")
			break;
		i++;
	}
	i = 1;

	while (y - i > -1 && f[y - i][x][0] != tile[0]) {
		v.push_back({ y - i, x });
		if (f[y - i][x] != "")
			break;
		i++;
	}
}

void field::diagonalMarks(vector<pair<int, int>>& v, string tile, int y, int x) {
	int i = 1;
	while (y + i < 8 && x + i < 8 && f[y + i][x + i][0] != tile[0]) {
		v.push_back({ y + i, x + i });
		if (f[y + i][x + i] != "")
			break;
		i++;
	}

	i = 1;
	while (y - i > -1 && x + i < 8 && f[y - i][x + i][0] != tile[0]) {
		v.push_back({ y - i, x + i });
		if (f[y - i][x + i] != "")
			break;
		i++;
	}
	i = 1;

	while (y + i < 8 && x - i > -1 && f[y + i][x - i][0] != tile[0]) {
		v.push_back({ y + i, x - i });
		if (f[y + i][x - i] != "")
			break;
		i++;
	}
	i = 1;

	while (y - i > -1 && x - i > -1 && f[y - i][x - i][0] != tile[0]) {
		v.push_back({ y - i, x - i });
		if (f[y - i][x - i] != "")
			break;
		i++;
	}
}