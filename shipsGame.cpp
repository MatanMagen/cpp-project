#include "shipsGame.h"

void ShipsGame::gameInfo(int* time, char ship)
{
	gotoxy(35, GameConfig::GAME_HEIGHT + 4);

	if (*time < 100)
	{
		cout << "0";
		if (*time < 10)
			cout << "0";
	}

	cout << *time;
	(*time)--;

	gotoxy(65, 22);

	if (ship == 'b')
		cout << "big ship  ";
	else if (ship == 's')
		cout << "small ship";
	else
		cout << "          ";
}

bool ShipsGame::run()
{
	int time = START_TIME, numLifes = START_LIFE, shipStatus = SHIP_CAN_PLAY;
	char lastShip = 'b';
	int keyPressed = 0;
	bool pauseMode = false, bigShipFinish = false, smallShipFinish = false, possibleNextGame = false;

	gameInfo(&time, lastShip);

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
			{
				if (!bigShipFinish)
					lastShip = 'b';
				else
					lastShip = ' ';
			}

			if (keyPressed == (int)GameConfig::eKeys::SWAP_SMALL_LOWER || keyPressed == (int)GameConfig::eKeys::SWAP_SMALL)
			{
				if (!smallShipFinish)
					lastShip = 's';
				else
					lastShip = ' ';
			}
		}

		Sleep(200);

		if (!pauseMode)
		{
			gameInfo(&time, lastShip);
			if (time == 0)
			{
				possibleNextGame = true;
				break;
			}

			if (keyPressed == (int)GameConfig::eKeys::ESC)
			{
				shipStatus = board.getships(0).move(GameConfig::eKeys::PAUSE, '@', board);
				shipStatus = board.getships(1).move(GameConfig::eKeys::PAUSE, '#', board);
				keyPressed = 0;
			}
			else
			{
				if (keyPressed != (int)GameConfig::eKeys::SWAP_BIG_LOWER && keyPressed != (int)GameConfig::eKeys::SWAP_SMALL_LOWER
					&& keyPressed != (int)GameConfig::eKeys::SWAP_BIG && keyPressed != (int)GameConfig::eKeys::SWAP_SMALL && keyPressed != 0)
				{
					if (lastShip == 'b' && !bigShipFinish)
					{
						shipStatus = board.getships(1).move((GameConfig::eKeys)keyPressed, '#', board);
						if (shipStatus == SHIP_FINISH)
						{
							bigShipFinish = true;
							lastShip = ' ';
						}
					}
					if (lastShip == 's' && !smallShipFinish)
					{
						shipStatus = board.getships(0).move((GameConfig::eKeys)keyPressed, '@', board);
						if (shipStatus == SHIP_FINISH)
						{
							smallShipFinish = true;
							smallShipFinish = ' ';
						}
					}
				}
			}
		}

		if (shipStatus == SHIP_DIED)
		{
			possibleNextGame = true;
			break;
		}
		
		if (smallShipFinish && bigShipFinish)
		{
			clrscr();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
			cout << "YOU WON!!!";
			possibleNextGame = false;
			break;
		}
	}

	return possibleNextGame;
}
