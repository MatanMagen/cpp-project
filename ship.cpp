#include "ship.h"

void Ship::init(const Point& head, char ch, int color)
{
	this->ch = ch;
	this->backgroundcolor = color;
	body[0] = head;
	body[0].draw(ch, backgroundcolor);
	for (int i = 1; i < 2; i++)
	{
		body[i] = body[i - 1];
		body[i].move((GameConfig::eKeys)0);
		body[i].draw(ch, backgroundcolor);
	}
}
void Ship::move(GameConfig::eKeys direction)
{
	body[1].draw(' ', GameConfig::COLORS[0]);
	for (int i = 1; i > 0; i--)
	{
		body[i] = body[i - 1];
	}
	body[0].move(direction);
	body[0].draw(ch, backgroundcolor);
}
