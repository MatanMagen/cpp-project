#ifndef BIG_SHIP_H
#define BIG_SHIP_H

#include "point.h"
#include "ship.h"

class big_ship
{
private:
	Point body[2][2];
	char ch;
	int backgroundcolor;

public:
	void init(Point& head, char ch, int color);
	void move(GameConfig::eKeys direction);
};

#endif

