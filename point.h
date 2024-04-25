#ifndef POINT_H
#define POINT_H

#include "gameConfig.h"

class Point
{
	int x;
	int y;
	int diff_x;
	int diff_y;

public:
	void init(int x, int y);
	void draw(char ch, int backcolor);
	void move(GameConfig::eKeys key);
	bool isCharacterAtPosition(int x, int y, char expectedChar);
	int getx() {
		return this->x;
	}
	int gety() {
		return this->y;
	}
	void setx(int x) {
		this->x = x;
	}
	void sety(int y) {
		this->y = y;
	}
};

#endif

