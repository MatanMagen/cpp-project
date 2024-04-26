#include "ship.h"
#include "board.h"
#include <conio.h>
#include <Windows.h>
#include "shipsGame.h"
#include "general.h"
#include "block.h"
#include "board.h"

void Ship::move(GameConfig::eKeys direction, char ch, Board& board)
{

	if (direction != GameConfig::eKeys::PAUSE)
	{

		for (int i = 0; i < size; i++)
		{
			pos[i].draw(' ', GameConfig::COLORS[0]);
		}

		for (int i = 0; i < size; i++)
		{
			board.getBoard()[pos[i].getY()][pos[i].getX() ] = ' ';
		}


		for (int i = 0; i < size; i++)
		{
			pos[i].move(direction);
			pos[i].draw(ch, GameConfig::COLORS[0]);
		}

		for (int i = 0; i < size; i++)
		{
			board.getBoard()[pos[i].getY()][pos[i].getX()] = ch;
		}

		
	}
	else
	{

	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
}
