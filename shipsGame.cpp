#include "shipsGame.h"
#include <fstream>

void ShipsGame::gameInfo(int* time, char ship, int numLifes)
{
	Point legend_pos = board.getLegend();

	gotoxy(legend_pos.getX() + 27, legend_pos.getY());

	if (*time < 100)
	{
		cout << "0";
		if (*time < 10)
			cout << "0";
	}

	cout << *time;
	(*time)--;

	gotoxy(legend_pos.getX() + 30, legend_pos.getY() + 1);
	for (int i = 0; i < START_LIFE; i++)
		cout << "\b \b";

	for (int i = 0; i < numLifes; i++)
		cout << "*";

	gotoxy(legend_pos.getX() + 27, legend_pos.getY() + 2);

	if (ship == 'b')
		cout << "big ship  ";
	else if (ship == 's')
		cout << "small ship";
	else
		cout << "          ";
}

int ShipsGame::run(int numLifes)
{
	int time = board.getTime(), shipStatus = SHIP_CAN_PLAY;
	char lastShip = 'b';
	int keyPressed = 0, possibleNextGame = GAME_WON;
	bool pauseMode = false, bigShipFinish = false, smallShipFinish = false, createrecording = true;
	

	ofstream recording("recording.txt");

	gameInfo(&time, lastShip, numLifes);

	while (true)
	{
		if (_kbhit())
		{
			keyPressed = _getch();

			if (pauseMode && keyPressed == (int)GameConfig::eKeys::EXIT)
			{
				if (createrecording)
				{
					gameInfo(&time, lastShip, numLifes);
					recording << time << " EXIT" << endl;
					recording.flush();
				}

				cout << "\nexit game tnx";
				possibleNextGame = GAME_STOPED;
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
				if (createrecording)
				{
					gameInfo(&time, lastShip, numLifes);
					recording << time << " ESC" << endl;
				}

			}
			if (keyPressed == (int)GameConfig::eKeys::SWAP_BIG_LOWER || keyPressed == (int)GameConfig::eKeys::SWAP_BIG)
			{
				if (!bigShipFinish)
					lastShip = 'b';
				else
					lastShip = ' ';

				if (createrecording)
				{
					gameInfo(&time, lastShip, numLifes);
					recording << time << " SWAP_BIG" << endl;
					recording.flush();
				}
			}

			if (keyPressed == (int)GameConfig::eKeys::SWAP_SMALL_LOWER || keyPressed == (int)GameConfig::eKeys::SWAP_SMALL)
			{
				if (!smallShipFinish)
					lastShip = 's';
				else
					lastShip = ' ';

				if (createrecording)
				{
					gameInfo(&time, lastShip, numLifes);
					recording << time << " SWAP_SMALL" << endl;
					recording.flush();
				}
			}
		}

		Sleep(200);

		if (!pauseMode)
		{
			gameInfo(&time, lastShip, numLifes);
			if (time <= 0)
			{
				possibleNextGame = GAME_LOST;
				break;
			}

			if (keyPressed == (int)GameConfig::eKeys::ESC)
			{
				shipStatus = board.getships(0).move(GameConfig::eKeys::PAUSE, board);
				shipStatus = board.getships(1).move(GameConfig::eKeys::PAUSE, board);
				keyPressed = 0;
			}
			else
			{
				if (keyPressed != (int)GameConfig::eKeys::SWAP_BIG_LOWER && keyPressed != (int)GameConfig::eKeys::SWAP_SMALL_LOWER
					&& keyPressed != (int)GameConfig::eKeys::SWAP_BIG && keyPressed != (int)GameConfig::eKeys::SWAP_SMALL && keyPressed != 0)
				{
					if (createrecording)
					{
						gameInfo(&time, lastShip, numLifes);
						recording << time << " " << char(keyPressed) << endl;
						recording.flush();
					}

					if (lastShip == 'b' && !bigShipFinish)
					{						
						shipStatus = board.getships(1).move((GameConfig::eKeys)keyPressed, board);
						if (shipStatus == SHIP_FINISH)
						{
							bigShipFinish = true;
							lastShip = ' ';
						}
					}
					if (lastShip == 's' && !smallShipFinish)
					{
						shipStatus = board.getships(0).move((GameConfig::eKeys)keyPressed, board);
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
			possibleNextGame = GAME_LOST;
			break;
		}
		
		if (smallShipFinish && bigShipFinish)
		{
			clrscr();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
			cout << "You have completed the stage";
			Sleep(500);
			possibleNextGame = GAME_WON;
			break;
		}
	}
	recording.close();
	return possibleNextGame;
}
