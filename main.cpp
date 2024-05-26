#include"main.h"

int main()
{
	menu();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
	gotoxy(0, GameConfig::GAME_HEIGHT + 4);
}

void runShipsGame(int blockColor, int shipColor, int wallColor, int winningColor)
{
	bool possibleNextGame = true;
	int numLifes = START_LIFE;

	while (numLifes > 0 && possibleNextGame)
	{
		ShipsGame theGame;

		clrscr();
		theGame.setColors(blockColor, shipColor, wallColor, winningColor);
		theGame.init();
		theGame.showMenu();
		RemainingLifes(numLifes);
		possibleNextGame = theGame.run();
		--numLifes;
	}

	RemainingLifes(numLifes);
}

void menu()
{
	int action = 0, haveColor = 0;
	Point point[GameConfig::GAME_WIDTH][GameConfig::GAME_HEIGHT];
	int blockColor = 15, shipColor = 15, wallColor = 15, winningColor = 15;

	while (action != 1 && action != 9)
	{
		cout << "Please select the desired action from the following menu:\n";
		cout << "(1) Start a new game\n(8) Present instructions and keys\n(9) EXIT\n";
		action = _getch() - '0';

		clrscr();
		if (action == 1)
		{
			cout << "Please select if you want color in the game:\n"
				"Press (1) to play with color\nPress any other key to play without color\n";
			haveColor = _getch() - '0';

			clrscr();
			if (haveColor == 1)
			{
				blockColor = 15;
				shipColor = 15;
				wallColor = 15;
				winningColor = 15;
			}

			runShipsGame(blockColor, shipColor, wallColor, winningColor);

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
			cout << "Exiting the game";
	}
}

void RemainingLifes(int numLifes)
{
	if (numLifes == 0)
	{
		clrscr();
		cout << "you lost the game";
	}
	else
	{
		gotoxy(38, GameConfig::GAME_HEIGHT + 5);
		for (int i = 0; i < START_LIFE; i++)
			cout << "\b \b";

		for (int i = 0; i < numLifes; i++)
			cout << "*";
	}
}