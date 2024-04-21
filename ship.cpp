#include "ship.h"

void Ship::init(Point& head, char ch, int color)
{
	this->ch = ch;
	this->backgroundcolor = color;
	body[0] = head;
	body[1].setx(head.getx() + 1);
	body[1].sety(head.gety());
	body[0].draw(ch, backgroundcolor);
	body[1].draw(ch, backgroundcolor);
}
void Ship::move(GameConfig::eKeys direction)
{
	body[1].draw(' ', GameConfig::COLORS[0]);
	body[1] = body[0];
	body[0].move(direction);
	body[0].draw(ch, backgroundcolor);
}