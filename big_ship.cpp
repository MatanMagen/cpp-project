#include "big_ship.h"
#include "point.h"

void big_ship::init(Point& head, char ch, int color)
{
	body[0][0] = head;

	body[0][1].setx(head.getx() + 1);
	body[0][1].sety(head.gety());

	body[1][0].setx(head.getx());
	body[1][0].sety(head.gety() + 1);

	body[1][1].setx(head.getx() + 1);
	body[1][1].sety(head.gety() + 1);

	this->ch = ch;
	this->backgroundcolor = color;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
			body[i][j].draw(ch, backgroundcolor);
	}

}
void big_ship::move(GameConfig::eKeys direction)
{
	if (direction == GameConfig::eKeys::DOWN || direction == GameConfig::eKeys::LOWER_DOWN || direction == GameConfig::eKeys::UP || direction == GameConfig::eKeys::LOWER_UP)
	{
		body[0][0].draw(' ', GameConfig::COLORS[0]);
		body[0][1].draw(' ', GameConfig::COLORS[0]);
		body[0][0] = body[1][0];
		body[0][1] = body[1][1];
		body[1][0].move(direction);
		body[1][1].move(direction);
		body[1][0].draw(ch, backgroundcolor);
		body[1][1].draw(ch, backgroundcolor);
		
	}
	else if (direction == GameConfig::eKeys::RIGHT || direction == GameConfig::eKeys::LOWER_RIGHT || direction == GameConfig::eKeys::LEFT || direction == GameConfig::eKeys::LOWER_LEFT)
	{
		body[0][0].draw(' ', GameConfig::COLORS[0]);
		body[1][0].draw(' ', GameConfig::COLORS[0]);
		body[0][0] = body[0][1];
		body[1][0] = body[1][1];
		body[0][1].move(direction);
		body[1][1].move(direction);
		body[0][1].draw(ch, backgroundcolor);
		body[1][1].draw(ch, backgroundcolor);
		
	}
	
}
