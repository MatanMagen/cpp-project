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
			runStep(keyPlay, numLifes, result, recording);
		}

		Sleep(200);

	}

	return 9;
}
