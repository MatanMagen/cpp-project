#include "shipsGame.h"
#include <fstream>

int ShipsGame::run(char mode, int numLifes, std::ofstream& result, std::ofstream& recording)
{
	int keyPlay = -1, statusGame = -1, shipStatus, lastStatus = SHIP_CAN_PLAY;
	char currShip = 'b';

	gameInfo(currShip, numLifes);
	while (true)
	{
		if (_kbhit())
		{

			keyPlay = _getch();
			if (keyPlay == (int)GameConfig::eKeys::ESC || keyPlay == (int)GameConfig::eKeys::SWAP_BIG || keyPlay == (int)GameConfig::eKeys::SWAP_BIG_LOWER
				|| keyPlay == (int)GameConfig::eKeys::SWAP_SMALL || keyPlay == (int)GameConfig::eKeys::SWAP_SMALL_LOWER)
			{
				currShip = status(keyPlay, currShip,lastStatus, numLifes, recording, mode);
			}
			
		}
		Sleep(200);
		shipStatus = runStep(keyPlay, currShip, lastStatus, numLifes, recording, mode);
		statusGame = resultGame(currShip, numLifes, shipStatus, result);
		if (statusGame == GAME_LOST || statusGame == GAME_WON)
		{
			break;
		}

	}
	
	// understand how to return the status of the game instead of 9
	return statusGame;
}
