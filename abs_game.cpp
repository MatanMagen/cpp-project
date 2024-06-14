#include "abs_Game.h"
#include "GameManager.h"

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

char abs_Game::status(int keyPlay, int lastKey, char lastShip, int lastStatus, int numLifes, char mode, int* statusGame)
{

	if (*statusGame == GAME_STOPED && keyPlay == (int)GameConfig::eKeys::EXIT)
	{
		clrscr();
		cout << "\nexit game tnx";
		*statusGame = GAME_EXIT;

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
	}

	if (keyPlay == (int)GameConfig::eKeys::SWAP_BIG_LOWER || keyPlay == (int)GameConfig::eKeys::SWAP_BIG)
	{
		if (lastStatus != BIG_SHIP_FINISH)
			lastShip = 'b';
		else
			lastShip = ' ';

		return lastShip;
	}

	if (keyPlay == (int)GameConfig::eKeys::SWAP_SMALL_LOWER || keyPlay == (int)GameConfig::eKeys::SWAP_SMALL)
	{
		if (lastStatus != SMALL_SHIP_FINISH)
			lastShip = 's';
		else
			lastShip = ' ';

		return lastShip;
	}

	return lastShip;
}

int abs_Game::runStep(int keyPlay,int lastKey, char* lastShip, int lastStatus, int numLifes, char mode)
{
	int shipStatus = lastStatus, temp;
	gameInfo(*lastShip, numLifes);
	if (keyPlay != (int)GameConfig::eKeys::SWAP_BIG_LOWER && keyPlay != (int)GameConfig::eKeys::SWAP_SMALL_LOWER
		&& keyPlay != (int)GameConfig::eKeys::SWAP_BIG && keyPlay != (int)GameConfig::eKeys::SWAP_SMALL && keyPlay != 0)
	{
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

int abs_Game::resultGame(char mode, int numLifes, int shipStatus, std::ofstream& result)
{
	int possibleNextGame = GAME_NEED_TO_RUN;

	if (shipStatus == SHIP_DIED || time <= 0)
	{
		possibleNextGame = GAME_LOST;

		if (mode == SAVE_MODE)
		{
			result << time << " " << possibleNextGame << " lost life" << endl;
			result.flush();
		}
	}

	if (shipStatus == BOTH_FINISH)
	{
		possibleNextGame = GAME_WON;

		if (mode == SAVE_MODE)
		{
			result << time << " " << possibleNextGame << " WIN!!!" << endl;
			result.flush();
		}
	}

	return possibleNextGame;
}

