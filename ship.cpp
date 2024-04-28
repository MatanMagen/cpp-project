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
	bool hitwall = false, hitBlock = false, toStop = false;
	int sizeBlock;
	char boardPlace, chBlock;
	Block block;

	if (direction != GameConfig::eKeys::PAUSE)
	{
		//check if not wall infront
		Point temp[4];
		for (int i = 0; i < size; i++)
		{
			temp[i] = pos[i];
			temp[i].move(direction);
		}

		for (int i = 0; i < size; i++)
		{
			boardPlace = board.getBoard()[temp[i].getY()][temp[i].getX()];
			if (boardPlace == 'W')
				hitwall = true;
			else if (boardPlace >= 'a' && boardPlace <= 'b')
			{
				hitBlock = true;
				chBlock = boardPlace;
			}
		}

		//actuall move
		if (!hitwall)
		{
			if (hitBlock)
			{
				block = board.getblock(chBlock);
				sizeBlock = block.getSize();
				//Checking if the ship can move the brick
				if (size == BIG_SHIP_SIZE && sizeBlock < MAX_MOVE_BIG_SHIP || size == SMALL_SHIP_SIZE && sizeBlock < MAX_MOVE_SMALL_SHIP)
					//returns the brick hit the wall
					toStop = block.move(direction, chBlock, board);
				else
					toStop = true;
			}

			if (!toStop)
			{
				for (int i = 0; i < size; i++)
				{
					pos[i].draw(' ', GameConfig::COLORS[0]);
				}

				for (int i = 0; i < size; i++)
				{
					board.getBoard()[pos[i].getY()][pos[i].getX()] = ' ';
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
		}
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
}
