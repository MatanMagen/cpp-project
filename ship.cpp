#include "ship.h"

#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>

void Ship::init(Point& head, char ch, int color)
{
	this->ch = ch;
	this->backgroundcolor = color;
	body[0] = head;
	body[1].setx(head.getx() + 1);
	body[1].sety(head.gety());
	body[0].draw(ch, backgroundcolor);
	body[1].draw(ch, backgroundcolor);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
}
void Ship::move(GameConfig::eKeys direction)
{
	if (direction != GameConfig::eKeys::PAUSE)
	{
		body[1].draw(' ', GameConfig::COLORS[0]);
		body[1] = body[0];
		body[0].move(direction);
		body[0].draw(ch, backgroundcolor);
	}
	else
	{
		body[0].draw(ch, backgroundcolor);
		body[1].draw(ch, backgroundcolor);
	}

<<<<<<< HEAD
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
=======
>>>>>>> c54c8ebdb3ae4d5a96ae78058f133d328ff67b6c
}