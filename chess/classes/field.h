#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>

using namespace std;
using namespace sf;

class field
{
protected:
	int checkFigX, checkFigY;
	void marking(string tile, int x, int y);
	vector<pair<int, int>> markedTiles;
	void switchMarks(vector<pair<int, int>> &v, string tile, int x, int y);
	void clearMarks();

	void pawnMarks(vector<pair<int, int>>& v, string tile, int y, int x);
	void diagonalMarks(vector<pair<int, int>> &v, string tile, int y, int x);
	void horizontalMarks(vector<pair<int, int>>& v, string tile, int y, int x);
	void horseMarks(vector<pair<int, int>>& v, string tile, int y, int x);
	void kingMarks(vector<pair<int, int>>& v, string tile, int y, int x);

public:

	char win;

	char checkColor = 'w';
	vector<vector<string> > f;
	map < char, map<char, Image>> figures;
	field();
	void check(Vector2i mousePos);
	vector<pair<int, int>> getMarkedTiles();
};