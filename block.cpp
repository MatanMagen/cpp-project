#include "ship.h"
#include "board.h"
#include "general.h"
#include "block.h"

bool Block::move(GameConfig::eKeys direction, char ch, Board& board)
{
	bool hitObject = false, needFall = false;
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
		if (boardPlace == 'W'|| boardPlace == '@' || boardPlace == '#')
			hitObject = true;
	}

	//actuall move
	if (!hitObject)
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
			pos[i].draw(ch, GameConfig::COLORS[backgroundColor]);
			board.getblock(ch).editPoint(i, pos[i]);
		}

		for (int i = 0; i < size; i++)
		{
			board.getBoard()[pos[i].getY()][pos[i].getX()] = ch;
		}

		//check for fall
		for (int i = 0; i < size; i++)
		{
			int x = board.getblock(ch).getPos(i).getX();
			int y = board.getblock(ch).getPos(i).getY();
			if (board.getBoard()[y][x - 1] == ' ')
			{
				needFall = true;
			}
		}

		if (needFall)
		{
			move(GameConfig::eKeys::DOWN, ch, board);
		}
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);

	return hitObject;
}


