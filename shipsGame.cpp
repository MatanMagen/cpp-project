#include "shipsGame.h"

void ShipsGame::gameTime(int* time)
{
	gotoxy(GameConfig::MIN_X + 35, GameConfig::GAME_HEIGHT + 4);
	
	if (*time < 100)
	{
		cout << "0";
		if (*time < 10)
			cout << "0";
	}

	cout << *time;
	(*time)--;
}

bool ShipsGame::run()
{
	int time = START_TIME, numLifes = START_LIFE;
	char lastShip = ' ';
	int keyPressed = 0;
	bool pauseMode = false, bigShipFinish = false, smallShipFinish = false, possibleNextGame = false;

	gameTime(&time);

	while (true)
	{
		if (_kbhit())
		{
			keyPressed = _getch();
			if (pauseMode && keyPressed == (int)GameConfig::eKeys::EXIT)
			{
				cout << "\nexit game tnx";
				possibleNextGame = false;
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
					board.show();
				}

			}
			if (keyPressed == (int)GameConfig::eKeys::SWAP_BIG_LOWER || keyPressed == (int)GameConfig::eKeys::SWAP_BIG)
				lastShip = 'b';
			if (keyPressed == (int)GameConfig::eKeys::SWAP_SMALL_LOWER || keyPressed == (int)GameConfig::eKeys::SWAP_SMALL)
				lastShip = 's';
		}

		Sleep(200);

		if (!pauseMode)
		{
			gameTime(&time);
			if (time == 0)
			{
				possibleNextGame = true;
				break;
			}

			if (keyPressed == (int)GameConfig::eKeys::ESC)
			{
				smallShipFinish = board.getships(0).move(GameConfig::eKeys::PAUSE, '@', board);
				bigShipFinish = board.getships(1).move(GameConfig::eKeys::PAUSE, '#', board);
				keyPressed = 0;
			}
			else
			{
				if (keyPressed != (int)GameConfig::eKeys::SWAP_BIG_LOWER && keyPressed != (int)GameConfig::eKeys::SWAP_SMALL_LOWER
					&& keyPressed != (int)GameConfig::eKeys::SWAP_BIG && keyPressed != (int)GameConfig::eKeys::SWAP_SMALL && keyPressed != 0)
				{
					if (lastShip == 'b' && !bigShipFinish)
						bigShipFinish = board.getships(1).move((GameConfig::eKeys)keyPressed, '#', board);
					if (lastShip == 's' && !smallShipFinish)
						smallShipFinish += board.getships(0).move((GameConfig::eKeys)keyPressed, '@', board);
				}
			}
		}

		if (smallShipFinish && bigShipFinish)
		{
			clrscr();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[WINNING_COLOR]);
			cout << "YOU WON!!!";
			possibleNextGame = false;
			break;
		}
	}

	return possibleNextGame;
}
