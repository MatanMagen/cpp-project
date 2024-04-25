#include <conio.h> // for kbhit+getch
#include <iostream>
#include <Windows.h> // for Sleep and colors
using namespace std;

#include "general.h"
#include "gameConfig.h"
#include "point.h"
#include "ship.h"
#include "shipsGame.h"

void testShipsGame();
int menu();

int main()
{
	testShipsGame();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
	gotoxy(0, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 4);
}

void testShipsGame()
{
	ShipsGame theGame;
	
	if (menu() == 1)
	{
		theGame.init();
		theGame.showMenu();
		theGame.run();
		theGame.freeMemory();
	}

}

int menu()
{
	int action = 0;
	Point point[GameConfig::GAME_WIDTH][GameConfig::GAME_HEIGHT];

	while (action != 1 && action != 9)
	{
		cout << "Please select the desired action from the following menu:\n";
		cout << "(1) Start a new game\n(8) Present instructions and keys\n(9) EXIT\n";
		cin >> action;

		if (action == 1)
		{
			clrscr();
			return 1;
		}
		else if (action == 8)
		{
			cout << "Two ships are trapped inside an ancient Egyptian tomb.\n"
				"A big one(size = 2 * 2) and a small one. Both ships\n"
				"cannot move through walls.At any point of time you can\n"
				"move either the big or the small ship. The big ship can\n"
				"move or carry blocks of total size 6. The small ship can\n"
				"move or carry blocks of total size 2. you shall finish\n"
				"thr screen in a given time by reaching the exit\n"
				"point on screen with both ships.\n\n"
				"the keys are:\n"
				"to move left press                - a or A\n"
				"to move right press               - d or D\n"
				"to move up press                  - w or W\n"
				"to move left press                - x or X\n"
				"to Switched to the Big Ship press - b or B\n"
				"Switched to the small Ship press  - s or S\n";
		}
		else if (action == 9)
		{
			cout << "Exiting the game";
			exit(1);
		}
	}

	return action;
}
