#include "ship.h"
#include "board.h"
#include <conio.h>
#include <Windows.h>
#include "shipsGame.h"
#include "general.h"
#include "block.h"


bool Block::move(GameConfig::eKeys direction, char ch, Board& board)
{
	bool hitwall = false, hitBlock = false;
	char boardPlace, chBlock;
	int blockX, blockY;
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
		if (boardPlace == 'W')
			hitwall = true;
	}

	//actuall move
	if (!hitwall)
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
			board.getblock(ch).editPoint(i, pos[i]);
		}

		for (int i = 0; i < size; i++)
		{
			board.getBoard()[pos[i].getY()][pos[i].getX()] = ch;
		}
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);

	return hitwall;
}


