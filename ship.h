#ifndef SHIP_H
#define SHIP_H

#include "point.h"
class Ship
{
private:
	Point body[2];
	char ch;
	int backgroundcolor;
public:
	void init(Point& head, char ch, int color);
	void move(GameConfig::eKeys direction);
	Point& getHead()
	{
		return body[0];
	}
};

#endif

