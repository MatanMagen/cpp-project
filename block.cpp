#include "ship.h"
#include "board.h"
#include "general.h"
#include "block.h"

bool Block::move(GameConfig::eKeys direction, char ch, Board& board, bool isCarried, int maxMove)
{
	bool hitObject = false, needFall = false, hitBlock = false;
	char boardPlace, chBlock, whichBlockHit;
	Block curr, next;
	int sizeNext;

	//check if not wall infront
	hitObject = ishitObject(direction, ch, board, &hitBlock, &whichBlockHit);

	if (hitBlock)
	{
		next = board.getblock(whichBlockHit);
		sizeNext = next.getSize();
		if(maxMove - sizeNext >= 0)
			next.move(direction, whichBlockHit, board, isCarried, maxMove - sizeNext);
		else
			return hitBlock;
	}
	

	//actuall move
	if (!hitObject)
	{
		for (int i = 0; i < size; i++)
		{
			pos[i].draw(' ', 15);
		}

		for (int i = 0; i < size; i++)
		{
			board.getBoard()[pos[i].getY()][pos[i].getX()] = ' ';
		}

		for (int i = 0; i < size; i++)
		{
			pos[i].move(direction);
			pos[i].draw(ch, backgroundColor);
			board.getblock(ch).editPoint(i, pos[i]);
		}

		for (int i = 0; i < size; i++)
		{
			board.getBoard()[pos[i].getY()][pos[i].getX()] = ch;
		}

		//check for fall
		needFall = toFall(direction, ch, board, isCarried);

		if (needFall)
		{
			hitObject = move(GameConfig::eKeys::DOWN, ch, board, isCarried, maxMove);
		}
	}

	return hitObject;
}

bool Block::ishitObject(GameConfig::eKeys direction, char ch, Board& board, bool *hitBlock, char* whichBlockHit)
{
	bool hitObject = false;
	char boardPlace;
	Block curr;

	//check if not wall infront
	Point temp[MAX_BlOCK_SIZE];
	for (int i = 0; i < size; i++)
	{
		temp[i] = pos[i];
		temp[i].move(direction);
	}
	for (int i = 0; i < size; i++)
	{
		boardPlace = board.getBoard()[temp[i].getY()][temp[i].getX()];
		if (boardPlace == 'W' || boardPlace == '@' || boardPlace == '#')
			hitObject = true;
		if (boardPlace >= 'a' && boardPlace <= 'c' && boardPlace != ch)
		{
			*hitBlock = true;
			*whichBlockHit = boardPlace;
		}
	}

	return hitObject;
}

bool Block::toFall(GameConfig::eKeys direction, char ch, Board& board, bool isCarried)
{
	char whichBlockHit;
	bool needFall = false, hitBlock = false;
	bool hitObject = ishitObject(direction, ch, board, &hitBlock, &whichBlockHit);
	
	if (isCarried)
	{
		if (direction == GameConfig::eKeys::LOWER_LEFT || direction == GameConfig::eKeys::LOWER_RIGHT || direction == GameConfig::eKeys::RIGHT || direction == GameConfig::eKeys::LEFT)
		{
			if (hitObject)
			{
				for (int i = 0; i < size; i++)
				{
					int x = board.getblock(ch).getPos(i).getX();
					int y = board.getblock(ch).getPos(i).getY();
					if (board.getBoard()[y + 1][x] == ' ')
					{
						needFall = true;
					}
				}
			}
		}
	}
	else {
		for (int i = 0; i < size; i++)
		{
			int x = board.getblock(ch).getPos(i).getX();
			int y = board.getblock(ch).getPos(i).getY();
			if (board.getBoard()[y + 1][x] == ' ')
			{
				needFall = true;
			}
		}
	}

	return needFall;
}

bool Block::isKilledShip(char ch, Board& board)
{
	bool killedShip = false;
	char boardPlace;

	//check if not wall infront
	Point temp[MAX_BlOCK_SIZE];
	for (int i = 0; i < size; i++)
	{
		temp[i] = pos[i];
		temp[i].move(GameConfig::eKeys::DOWN);
	}
	for (int i = 0; i < size; i++)
	{
		boardPlace = board.getBoard()[temp[i].getY()][temp[i].getX()];
		if (boardPlace == '@' && size >= MAX_MOVE_SMALL_SHIP)
			killedShip = true;
		else if (boardPlace == '#' && size >= MAX_MOVE_BIG_SHIP)
			killedShip = true;
	}

	return killedShip;
}
