#include "abs_Game.h"
#include "GameManager.h"
#include <fstream>
#include <iostream>
#include <string>

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

char abs_Game::status(int keyPlay, int lastKey, char lastShip, int lastStatus, int numLifes, std::fstream& recording, char mode, int* statusGame)
{

	if (*statusGame == GAME_STOPED && keyPlay == (int)GameConfig::eKeys::EXIT)
	{
		if (mode == SAVE_MODE)
		{
			if (keyPlay != lastKey)
			{
				recording << time << " " << keyPlay << endl;
				recording.flush();
			}
		}

		clrscr();
		cout << "\nexit game tnx";
		*statusGame = GAME_EXIT;

		if (mode == SAVE_MODE)
		{
			if (keyPlay != lastKey)
			{
				recording << time << " " << keyPlay << endl;
				recording.flush();
			}
		}

		return lastShip;
	}
	if (keyPlay == (int)GameConfig::eKeys::ESC)
	{
		board.getships(0).move(GameConfig::eKeys::PAUSE, board);
		board.getships(1).move(GameConfig::eKeys::PAUSE, board);
		keyPlay = 0;
		if (*statusGame != GAME_STOPED)
		{
			clrscr();
			*statusGame = GAME_STOPED;
			cout << "Game paused, press ESC again to continue or 9 to Exit";
		}
		else
		{
			clrscr();
			*statusGame = GAME_NEED_TO_RUN;
			board.show();
		}
		if (mode == SAVE_MODE)
		{
			if (keyPlay != lastKey)
			{
				recording << time << " " << keyPlay << endl;
				recording.flush();
			}
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
			if (keyPlay != lastKey)
			{
				recording << time << " " << keyPlay << endl;
				recording.flush();
			}
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
			if (keyPlay != lastKey)
			{
				recording << time << " " << keyPlay << endl;
				recording.flush();
			}
		}

		return lastShip;
	}

	return lastShip;
}

int abs_Game::runStep(int keyPlay,int lastKey, char* lastShip, int lastStatus, int numLifes, std::fstream& recording, char mode)
{
	int shipStatus = lastStatus, temp;
	gameInfo(*lastShip, numLifes);
	if (keyPlay != (int)GameConfig::eKeys::SWAP_BIG_LOWER && keyPlay != (int)GameConfig::eKeys::SWAP_SMALL_LOWER
		&& keyPlay != (int)GameConfig::eKeys::SWAP_BIG && keyPlay != (int)GameConfig::eKeys::SWAP_SMALL && keyPlay != 0)
	{
		if (mode == SAVE_MODE)
		{
			if (keyPlay != lastKey)
			{
				recording << time << " " << keyPlay << endl;
				recording.flush();
			}
		}

		if (*lastShip == 'b' && lastStatus != BIG_SHIP_FINISH)
		{
			temp = board.getships(1).move((GameConfig::eKeys)keyPlay, board);
			if (temp == SHIP_FINISH)
			{
				if (shipStatus == SMALL_SHIP_FINISH)
					shipStatus = BOTH_FINISH;
				else
				{
					shipStatus = BIG_SHIP_FINISH;
					*lastShip = ' ';
				}
			}
		}
		if (*lastShip == 's' && lastStatus != SMALL_SHIP_FINISH)
		{
			temp = board.getships(0).move((GameConfig::eKeys)keyPlay, board);
			if (temp == SHIP_FINISH)
			{
				if (shipStatus == BIG_SHIP_FINISH)
					shipStatus = BOTH_FINISH;
				else
				{
					shipStatus = SMALL_SHIP_FINISH;
					*lastShip = ' ';
				}
			}
		}
	}

	return shipStatus;
}

int abs_Game::resultGame(char lastShip, int numLifes, int shipStatus, std::fstream& result)
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

	if (shipStatus == BOTH_FINISH)
	{
		possibleNextGame = GAME_WON;
		result << time << " WIN!!!" << endl;
		result.flush();
		clrscr();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
	}

	return possibleNextGame;
}
