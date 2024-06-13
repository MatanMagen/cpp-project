#include "loadGame.h"

int loadGame::run(char mode, int numLifes, std::fstream& result, std::fstream& recording)
{
	// kbhit = time from file
	// _getch = second argument from  curr line in file

	int keyPlay = -1, lastKey = -1, statusGame = GAME_NEED_TO_RUN, shipStatus = SHIP_CAN_PLAY;
	char currShip = 'b';

	gameInfo(currShip, numLifes);

	//first time from file
	while (true)
	{
		if (_kbhit())// is time from file is now
		{
			keyPlay = _getch();// read the action from file
			currShip = status(keyPlay, lastKey, currShip, shipStatus, numLifes, recording, mode, &statusGame);
			// read the next time
		}
		if (statusGame == GAME_NEED_TO_RUN)
		{
			Sleep(200);
			shipStatus = runStep(keyPlay, lastKey, &currShip, shipStatus, numLifes, recording, mode);
			statusGame = resultGame(currShip, numLifes, shipStatus, result);
		}
		if (statusGame == GAME_LOST || statusGame == GAME_WON || statusGame == GAME_EXIT)
			break;

		lastKey = keyPlay;
	}

	return statusGame;
}
