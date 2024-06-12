#include "shipsGame.h"
#include <fstream>

int ShipsGame::run(char mode, int numLifes, std::ofstream& result, std::ofstream& recording)
{
	int keyPlay;

	while (true)
	{
		if (_kbhit())
		{
			keyPlay = _getch();
			status(keyPlay, numLifes,result, recording);
		}

		Sleep(200);

		runStep(pauseMode, lastShip, numLifes, result, recording);
		resultGame(pauseMode, lastShip, numLifes, shipStatus, smallShipFinish, bigShipFinish, result);
	}

	return 9;
}
