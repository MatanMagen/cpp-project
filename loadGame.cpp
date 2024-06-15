#include "loadGame.h"

int loadGame::run(char mode, int numLifes, std::ifstream& recording, int *timeStatus)
{
	// kbhit = time from file
	// _getch = second argument from  curr line in file

	int keyPlay = -1, lastKey = -1, statusGame = GAME_NEED_TO_RUN, shipStatus = SHIP_CAN_PLAY;
	char currShip = 'b';
	std::string line;
	int firstPart, secondPart;
	ofstream temp;

	gameInfo(currShip, numLifes, mode);

	getline(recording, line);
	std::istringstream lineStream(line);

	lineStream >> firstPart >> secondPart; // Extract the two parts

	//first time from file
	while (true)
	{
		if (getTime() == firstPart)// is time from file is now
		{
			keyPlay = secondPart;// read the action from file
			currShip = status(keyPlay, lastKey, currShip, shipStatus, numLifes, mode, &statusGame);
			// read the next time
			if (getline(recording, line))
			{
				std::istringstream lineStream(line);
				lineStream >> firstPart >> secondPart;
			}
		}
		if (statusGame == GAME_NEED_TO_RUN)
		{
			if (mode != SILENT_MODE)
				Sleep(200);
			shipStatus = runStep(keyPlay, lastKey, &currShip, shipStatus, numLifes, mode);
			statusGame = resultGame(mode, numLifes, shipStatus, temp);
		}
		if (statusGame == GAME_LOST || statusGame == GAME_WON || statusGame == GAME_EXIT)
		{
			*timeStatus = getTime() + 1;
			break;
		}

		lastKey = keyPlay;
	}

	recording.close();

	return statusGame;
}
