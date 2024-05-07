#ifndef POINT_H
#define POINT_H

#include "gameConfig.h"
#include "general.h"
#include <iostream>
#include <Windows.h>
#include <stdbool.h>
using namespace std;

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
	void set(int x1, int y1) {
		x = x1;
		y = y1;
		diff_x = 0;
		diff_y = 0;
	}
	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
};

#endif

