#include "ship.h"
#include "board.h"
#include <conio.h>
#include <Windows.h>
#include "shipsGame.h"
#include "general.h"
#include "block.h"
#include "board.h"

//function move the ship and return if ship finshed the game 
bool Ship::move(GameConfig::eKeys direction, char ch, Board& board)
{
	bool hitwall = false, hitBlock = false, toStop = false,hitOtherPlayer = false;
	int sizeBlock;
	char boardPlace, chBlock;
	Block block;

	if (direction != GameConfig::eKeys::PAUSE)
	{
		//check if wall or blocks or finish point infront
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
			else if (boardPlace >= 'a' && boardPlace <= 'c')
			{
				hitBlock = true;
				chBlock = boardPlace;
			}
			else if (boardPlace == 'X')
			{
				for (int i = 0; i < size; i++)
				{
					pos[i].draw(' ', GameConfig::COLORS[0]);
					board.getBoard()[pos[i].getY()][pos[i].getX()] = ' ';
				}

				return true;
			}
			else if ((ch != '#' && boardPlace == '#') || (ch != '@' && boardPlace == '@')) //both of them in the same place
			{
				hitOtherPlayer = true;
			}
		}

		//actuall move
		if (!hitwall && !hitOtherPlayer)
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
	return false;
}
