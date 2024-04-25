#include "shipsGame.h"
#include "ship.h"
#include "big_ship.h"
#include "general.h"
#include "block.h"

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
	block1 = new Block;
	//block2 = new Block;

	Point head, bigHead, block1Head, block2Head;
	head.init(7 % GameConfig::GAME_WIDTH, 7 % GameConfig::GAME_HEIGHT);
	smallShip->init(head, '#', GameConfig::COLORS[2]);

	bigHead.init(1 % GameConfig::GAME_WIDTH, 1 % GameConfig::GAME_HEIGHT);
	bigShip->init(bigHead, '@', GameConfig::COLORS[3]);
	
	block1Head.init(1 % GameConfig::GAME_WIDTH, 10 % GameConfig::GAME_HEIGHT);
	block1->init(block1Head, 'a', 2);
	
	//block2Head.init(5 % GameConfig::GAME_WIDTH, 5 % GameConfig::GAME_HEIGHT);
	//block2->init(bigHead, 'b', 6);
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
		cout << "W";

		gotoxy(col, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y);
		cout << "W";

		gotoxy(col, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 2);
		cout << "W";
	}

	for (int row = GameConfig::MIN_Y - 1; row <= GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 2; row++)
	{
		gotoxy(GameConfig::MIN_X - 1, row);
		cout << "W";

		gotoxy(GameConfig::GAME_WIDTH + GameConfig::MIN_X, row);
		cout << "W";
	}

	gotoxy(GameConfig::MIN_X + 1, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 1);
	cout << "The time Remaining is ";
	RemainingLifes();
}

void ShipsGame::gameTime(int* time)
{
	gotoxy(GameConfig::MIN_X + 23, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 1);

	if (*time < 100)
	{
		cout << "0";
		if (*time < 10)
			cout << "0";
	}
	
	cout << *time;
	(*time)--;

	if (*time == 0)
	{
		clrscr();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
		cout << "you lost the game";
		exit(0);
	}
}

void ShipsGame::RemainingLifes()
{
	int numLifes = 3;
	gotoxy(GameConfig::MIN_X + 50, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 1);
	cout << "The lifes Remaining is :";
	for (int i = 0; i < numLifes; i++)
		cout << "* ";
}

void ShipsGame::run()
{
	int time = START_TIME;
	char lastShip = ' ';
	int keyPressed = 0, action;
	bool pauseMode = false;

	gameTime(&time);

	while (true)
	{
		if (_kbhit())
		{
			keyPressed = _getch();
			if (keyPressed == (int)GameConfig::eKeys::EXIT)
			{
				cout << "exit game tnx";
				break;
			}
			if (keyPressed == (int)GameConfig::eKeys::ESC)
			{
				if (!pauseMode)
				{
					clrscr();
					pauseMode = true;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
					cout << "Game paused, press ESC again to continue or 9 to Exit";
				}
				else
				{
					clrscr();
					pauseMode = false;
					drawBorder();
				}

			}
			if (keyPressed == (int)GameConfig::eKeys::SWAP_BIG_LOWER || keyPressed == (int)GameConfig::eKeys::SWAP_BIG)
				lastShip = 'b';
			if (keyPressed == (int)GameConfig::eKeys::SWAP_SMALL_LOWER || keyPressed == (int)GameConfig::eKeys::SWAP_SMALL)
				lastShip = 's';
		}

		Sleep(500);

		if (!pauseMode)
		{
			gameTime(&time);

			if (keyPressed == (int)GameConfig::eKeys::ESC)
			{
				bigShip->move(GameConfig::eKeys::PAUSE);
				smallShip->move(GameConfig::eKeys::PAUSE);
			}
			else
			{
				if (lastShip == 'b')
					bigShip->move((GameConfig::eKeys)keyPressed);
				if (lastShip == 's')
					smallShip->move((GameConfig::eKeys)keyPressed);
			}

		}

	}
}
