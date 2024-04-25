#include "block.h"

void Block::init(Point& head, char ch, int size)
{
	body[0] = head;
	body[0].draw(ch, GameConfig::COLORS[0]);

	for (int i = 1; i < size; i++)
	{
		body[i].setx(body[i - 1].getx() + 1);
		body[i].sety(body[i - 1].gety());
		body[i].draw(ch, GameConfig::COLORS[0]);
	}

	this->ch = ch;
}
void Block::move(GameConfig::eKeys direction)
{
	body[sizeBlock - 1].draw(' ', GameConfig::COLORS[0]);
	for (int i = sizeBlock; i > 0; i--)
	{
		body[i] = body[i - 1];
	}
	body[0].move(direction);
	body[0].draw(ch, GameConfig::COLORS[0]);
}