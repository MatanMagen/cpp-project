#include "shipsGame.h"

int ShipsGame::run(char mode, int numLifes, std::ofstream& result, std::ofstream& recording)
{
	int keyPlay = -1, lastKey = -1, statusGame = GAME_NEED_TO_RUN, shipStatus = SHIP_CAN_PLAY;
	char currShip = 'b';

	gameInfo(currShip, numLifes, mode);
	while (true)
	{
		if (_kbhit())
		{
			keyPlay = _getch();
			currShip = status(keyPlay, lastKey, currShip, shipStatus, numLifes, mode, &statusGame);
		}
		if (statusGame == GAME_NEED_TO_RUN)
		{
			Sleep(200);
			shipStatus = runStep(keyPlay, lastKey, &currShip, shipStatus, numLifes, mode);
			statusGame = resultGame(mode, numLifes, shipStatus, result);
		}

		if (keyPlay == (int)GameConfig::eKeys::DOWN || keyPlay == (int)GameConfig::eKeys::LOWER_DOWN ||
			keyPlay == (int)GameConfig::eKeys::LOWER_LEFT || keyPlay == (int)GameConfig::eKeys::LEFT ||
			keyPlay == (int)GameConfig::eKeys::LOWER_RIGHT || keyPlay == (int)GameConfig::eKeys::RIGHT ||
			keyPlay == (int)GameConfig::eKeys::LOWER_UP || keyPlay == (int)GameConfig::eKeys::UP ||
			keyPlay == (int)GameConfig::eKeys::SWAP_SMALL || keyPlay == (int)GameConfig::eKeys::SWAP_SMALL_LOWER ||
			keyPlay == (int)GameConfig::eKeys::SWAP_BIG_LOWER || keyPlay == (int)GameConfig::eKeys::SWAP_BIG)
		{
			if (mode == SAVE_MODE)
			{
				if (keyPlay != lastKey)
				{
					recording << getTime() << " " << keyPlay << endl;
					recording.flush();
				}
			}
		}

		if (statusGame == GAME_LOST || statusGame == GAME_WON || statusGame == GAME_EXIT)		
			break;

		lastKey = keyPlay;
	}

	return statusGame;
}
