#include "abs_Game.h"
#include "GameManager.h"
#include <fstream>

void abs_Game::gameInfo(char ship, int numLifes)
{
	Point legend_pos = board.getLegend();

	gotoxy(legend_pos.getX() + 27, legend_pos.getY());

	if (time < 100)
	{
		cout << "0";
		if (time < 10)
			cout << "0";
	}

	cout << time;
	time--;

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

char abs_Game::status(int keyPlay, char lastShip , int lastStatus ,int numLifes, std::ofstream& recording, char mode)
{
	int possibleNextGame = GAME_WON;
	bool pauseMode = false;

	if (keyPlay == (int)GameConfig::eKeys::ESC)
	{
		board.getships(0).move(GameConfig::eKeys::PAUSE, board);
		board.getships(1).move(GameConfig::eKeys::PAUSE, board);
		keyPlay = 0;
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
		if (mode == SAVE_MODE)
		{
			recording << time << keyPlay << endl;
			recording.flush();
		}

		if (pauseMode && _getch() == (int)GameConfig::eKeys::EXIT)
		{
			if (mode == SAVE_MODE)
			{
				recording << time << keyPlay << endl;
				recording.flush();
			}

			cout << "\nexit game tnx";
			possibleNextGame = GAME_STOPED;

			if (mode == SAVE_MODE)
			{
				recording << time << keyPlay << endl;
				recording.flush();
			}
			else
			{
				clrscr();
				pauseMode = false;
				board.show();
			}
			if (mode == SAVE_MODE)
			{
				recording << time << keyPlay << endl;
				recording.flush();
			}
			return lastShip;
		}
	}

	if (keyPlay == (int)GameConfig::eKeys::SWAP_BIG_LOWER || keyPlay == (int)GameConfig::eKeys::SWAP_BIG)
	{
		if (lastStatus != BIG_SHIP_FINISH)
			lastShip = 'b';
		else
			lastShip = ' ';

		if (mode == SAVE_MODE)
		{
			recording << time << keyPlay << endl;
			recording.flush();
		}

		return lastShip;
	}

	if (keyPlay == (int)GameConfig::eKeys::SWAP_SMALL_LOWER || keyPlay == (int)GameConfig::eKeys::SWAP_SMALL)
	{
		if (lastStatus != SMALL_SHIP_FINISH)
			lastShip = 's';
		else
			lastShip = ' ';

		if (mode == SAVE_MODE)
		{
			recording << time << keyPlay << endl;
			recording.flush();
		}

		return lastShip;
	}
}

int abs_Game::runStep(int keyPlay,char lastShip, int lastStatus, int numLifes, std::ofstream& recording, char mode)
{
	int shipStatus = lastStatus;
	gameInfo(lastShip, numLifes);
	if (keyPlay != (int)GameConfig::eKeys::SWAP_BIG_LOWER && keyPlay != (int)GameConfig::eKeys::SWAP_SMALL_LOWER
		&& keyPlay != (int)GameConfig::eKeys::SWAP_BIG && keyPlay != (int)GameConfig::eKeys::SWAP_SMALL && keyPlay != 0)
	{
		if (mode == SAVE_MODE)
		{
			recording << time << keyPlay << endl;
			recording.flush();
		}

		if (lastShip == 'b' && lastStatus != BIG_SHIP_FINISH)
		{
			shipStatus = board.getships(1).move((GameConfig::eKeys)keyPlay, board);
			if (shipStatus == SHIP_FINISH)
			{
				if (lastStatus == SMALL_SHIP_FINISH)
				{
					shipStatus = BOTH_FINISH;
				}
				shipStatus = BIG_SHIP_FINISH;
			}
		}
		if (lastShip == 's' && lastStatus != SMALL_SHIP_FINISH)
		{
			shipStatus = board.getships(0).move((GameConfig::eKeys)keyPlay, board);
			if (shipStatus == SHIP_FINISH)
			{
				if (lastStatus == BIG_SHIP_FINISH)
				{
					shipStatus = BOTH_FINISH;
				}
				shipStatus = SMALL_SHIP_FINISH;
			}
		}
	}
	return shipStatus;
}

int abs_Game::resultGame(char lastShip, int numLifes, int shipStatus, std::ofstream& result)
{
	int possibleNextGame = GAME_NEED_TO_RUN;
	if (time <= 0)
	{
		result << "time over -> lost life" << endl;
		result.flush();
		possibleNextGame = GAME_LOST;
	}

	if (shipStatus == SHIP_DIED)
	{
		result << time << " lost life" << endl;
		result.flush();
		possibleNextGame = GAME_LOST;
	}

	if (shipStatus == BOTH_FINISH )
	{
		possibleNextGame = GAME_WON;
		result << time << " WIN!!!" << endl;
		result.flush();
		clrscr();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
		cout << "You have completed the stage";
		Sleep(500);
	}

	return possibleNextGame;
}
