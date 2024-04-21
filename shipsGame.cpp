#include "shipsGame.h"
#include "ship.h"
#include "big_ship.h"
#include "general.h"

#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

void ShipsGame::init()
{
	drawBorder();
	smallShip = new Ship;
	bigShip = new big_ship;

	Point head, bigHead;
	head.init(7 % GameConfig::GAME_WIDTH, 7 % GameConfig::GAME_HEIGHT);
	smallShip->init(head, '#', GameConfig::COLORS[2]);

	bigHead.init(1 % GameConfig::GAME_WIDTH, 1 % GameConfig::GAME_HEIGHT);
	bigShip->init(bigHead, '@', GameConfig::COLORS[3]);
}

void ShipsGame::freeMemory()
{
	//delete[]allShips;
}

void ShipsGame::drawBorder()
{
	for (int col = GameConfig::MIN_X; col < GameConfig::GAME_WIDTH + GameConfig::MIN_X; col++)
	{
		gotoxy(col, GameConfig::MIN_Y - 1);
		cout << "-";

		gotoxy(col, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y);
		cout << "-";
	}

	for (int row = GameConfig::MIN_Y - 1; row <= GameConfig::GAME_HEIGHT + GameConfig::MIN_Y; row++)
	{
		gotoxy(GameConfig::MIN_X - 1, row);
		cout << "|";

		gotoxy(GameConfig::GAME_WIDTH + GameConfig::MIN_X, row);
		cout << "|";
	}
}
	
void ShipsGame::run()
{
	char lastShip = ' ';
	int keyPressed = 0;

	while (true)
	{
		if (_kbhit())
		{
			keyPressed = _getch();
			if (keyPressed == (int)GameConfig::eKeys::ESC)
				break;
			if (keyPressed == (int)GameConfig::eKeys::SWAP_BIG_LOWER || keyPressed == (int)GameConfig::eKeys::SWAP_BIG)
				lastShip = 'b';
			if (keyPressed == (int)GameConfig::eKeys::SWAP_SMALL_LOWER || keyPressed == (int)GameConfig::eKeys::SWAP_SMALL)
				lastShip = 's';
		}
		Sleep(500);

		if(lastShip == 'b')
			bigShip->move((GameConfig::eKeys)keyPressed);
		if(lastShip == 's')
			smallShip->move((GameConfig::eKeys)keyPressed);
	}
}
	
