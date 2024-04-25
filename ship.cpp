#include "ship.h"
#include "board.h"

#include <Windows.h>

void Ship::move(GameConfig::eKeys direction, char ch)
{
	Board board;

	if (direction != GameConfig::eKeys::PAUSE)
	{
		/*pos[1].draw(' ', GameConfig::COLORS[0]);
		pos[1] = pos[0];
		pos[0].move(direction);
		pos[0].draw('@', GameConfig::COLORS[0]);*/

		for (int i = 0; i < size; i++)
		{
			pos[i].draw(' ', GameConfig::COLORS[0]);
		}

		for (int i = 0; i < size; i++)
		{
			pos[i].move(direction);
			pos[i].draw(ch, GameConfig::COLORS[0]);
		}
		
	}
	else
	{
		for (int i = 0; i < size; i++)
			pos[i].draw(ch, GameConfig::COLORS[0]);
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
}
