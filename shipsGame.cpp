#include "shipsGame.h"

int ShipsGame::run(char mode, int numLifes, std::ofstream& result, std::ofstream& recording)
{
	int keyPlay = -1, statusGame = GAME_NEED_TO_RUN, shipStatus = SHIP_CAN_PLAY;
	char currShip = 'b';

	gameInfo(currShip, numLifes);
	while (true)
	{
		if (_kbhit())
		{
			keyPlay = _getch();
			currShip = status(keyPlay, currShip, shipStatus, numLifes, recording, mode, &statusGame);
		}
		if (statusGame == GAME_NEED_TO_RUN)
		{
			Sleep(200);
			shipStatus = runStep(keyPlay, &currShip, shipStatus, numLifes, recording, mode);
			statusGame = resultGame(currShip, numLifes, shipStatus, result);
		}
		if (statusGame == GAME_LOST || statusGame == GAME_WON ||statusGame == GAME_EXIT)
			break;
	}

	return statusGame;
}
