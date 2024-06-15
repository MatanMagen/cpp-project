#include "ship.h"
#include "board.h"
#include "block.h"

//function move the ship and return if ship finshed the game 
int Ship::move(GameConfig::eKeys direction, Board& board, char mode)
{
	bool hitwall = false, hitBlock = false, toStop = false, hitOtherPlayer = false, carryingBrick = false;
	int sizeBlock, xBlock, yBlock;
	char boardPlace, chBlock;
	Block block;
	
	if (direction != GameConfig::eKeys::PAUSE)
	{
		//check if carrying a brick
		for (int i = 0; i < size; i++)
		{
			int x = pos[i].getX();
			int y = pos[i].getY();
			if (board.getBoard()[y - 1][x] >= 'a' && board.getBoard()[y - 1][x] <= 'z')
			{
				xBlock = x;
				yBlock = y;
				chBlock = board.getBoard()[y - 1][x];
				block = board.getblock(chBlock);
				sizeBlock = block.getSize();

				if (sizeBlock <= maxMove) 
					carryingBrick = true;
				else
					return SHIP_DIED;
			}
		}

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
			else if (boardPlace >= 'a' && boardPlace <= 'z')
			{
				hitBlock = true;
				chBlock = boardPlace;
			}
			else if (boardPlace == 'X')
			{
				for (int i = 0; i < size; i++)
				{
					if(mode != SILENT_MODE)
						pos[i].draw(' ', 15);
					board.getBoard()[pos[i].getY()][pos[i].getX()] = ' ';
				}

				return SHIP_FINISH;
			}
			else if ((shipType != '#' && boardPlace == '#') || (shipType != '@' && boardPlace == '@')) //both of them in the same place
				hitOtherPlayer = true;
		}

		//actuall move
		if (!hitwall && !hitOtherPlayer)
		{
			if (hitBlock || carryingBrick)
			{
				if (!(carryingBrick && (direction == GameConfig::eKeys::LOWER_DOWN || direction == GameConfig::eKeys::DOWN)))
				{
					block = board.getblock(chBlock);
					sizeBlock = block.getSize();
					//Checking if the ship can move the brick
					if (sizeBlock <= maxMove) {
						if (block.move(direction, chBlock, board, carryingBrick, maxMove - sizeBlock))
						{
							if (block.isKilledShip(shipType, board))
								return SHIP_DIED;

							for (int i = 0; i < size; i++)
							{
								boardPlace = board.getBoard()[temp[i].getY()][temp[i].getX()];
								if (boardPlace == 'W' || (boardPlace >= 'a' && boardPlace <= 'z') || (shipType != '#' && boardPlace == '#') || (shipType != '@' && boardPlace == '@'))
									toStop = true;
							}
						}
					}
				}
			}

			if (!toStop)
			{
				for (int i = 0; i < size; i++)
				{
					if (mode != SILENT_MODE)
						pos[i].draw(' ', GameConfig::COLORS[0]);
				}

				for (int i = 0; i < size; i++)
				{
					board.getBoard()[pos[i].getY()][pos[i].getX()] = ' ';
				}

				for (int i = 0; i < size; i++)
				{
					pos[i].move(direction);
					if (mode != SILENT_MODE)
						pos[i].draw(shipType, GameConfig::COLORS[0]);
				}

				for (int i = 0; i < size; i++)
				{
					board.getBoard()[pos[i].getY()][pos[i].getX()] = shipType;
				}

				if (carryingBrick)
				{
					block = board.getblock(chBlock);
					sizeBlock = block.getSize();

					if(block.toFall(direction, chBlock, board, carryingBrick))
						toStop = block.move(GameConfig::eKeys::DOWN, chBlock, board, !carryingBrick, maxMove - sizeBlock);
					
					if(direction == GameConfig::eKeys::LOWER_DOWN || direction == GameConfig::eKeys::DOWN)
						toStop = block.move(direction, chBlock, board, carryingBrick, maxMove - sizeBlock);
				}
			}
		}
	}

	return SHIP_CAN_PLAY;
}
