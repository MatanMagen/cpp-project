#include "gameManager.h"

void GameManager::playGame(int argc, char* argv[])
{
	bool isSilent = false;
	char mode = ' ';

	//find screens
	std::string pattern = ".screen";
	fs::path currentDir = fs::current_path();
	std::string screens[3];
	int numScreens = 0;

	for (const auto& entry : fs::directory_iterator(currentDir)) {
		if (fs::is_regular_file(entry.path())) {
			std::string filename = entry.path().filename().string();
			if (filename.find(pattern) != std::string::npos) {
				screens[numScreens] = filename;
				numScreens++;
			}
		}
	}

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-load") == 0)
			mode = LOAD_MODE;

		else if (strcmp(argv[i], "-silent") == 0)
			isSilent = true;
			
		else if (strcmp(argv[i], "-save") == 0)
			mode = SAVE_MODE; //recording game
	}
	
	if (mode == LOAD_MODE && isSilent)
		mode = SILENT_MODE;
	
	if (mode == LOAD_MODE || mode == SILENT_MODE) //playing regular game from the keyboard
		runLoadGame(15, 15, 15, 15, screens, mode);
	else
		menu(screens, numScreens, mode);
}

void GameManager::menu(std::string* screens, int numScreens, char mode)
{
	int action = 0, haveColor = 0;
	Point point[GameConfig::GAME_WIDTH][GameConfig::GAME_HEIGHT];
	int blockColor = 15, shipColor = 15, wallColor = 15, winningColor = 15;
	int screenPlay = 0;

	if (numScreens == 0)
	{
		cout << "There are no existing screens. Unable to play\nExiting the game";
		return;
	}

	while (action != 1 && action != 2 && action != 9)
	{
		cout << "Please select the desired action from the following menu:\n"
			"(1) Start a new game\n(2) Play a specific screen\n"
			"(8) Present instructions and keys\n(9) EXIT\n";
		action = _getch() - '0';

		clrscr();
		if (action == 1)
		{
			cout << "Please select if you want color in the game:\n"
				"Press (1) to play with color\nPress any other key to play without color\n";
			haveColor = _getch() - '0';

			clrscr();
			if (haveColor == 1)
			{
				blockColor = 15;
				shipColor = 15;
				wallColor = 15;
				winningColor = 15;
			}

			runShipGame(blockColor, shipColor, wallColor, winningColor, screens, mode, false, screenPlay);
		}
		else if (action == 2)
		{
			int i = 0;

			cout << "Please select which screen you would like to play\n";

			for (int i = 0; i < 3; i++)
				std::cout << i + 1 << ". " << screens[i] << "\n";

			screenPlay = _getch() - '1';
			runShipGame(blockColor, shipColor, wallColor, winningColor, screens, mode, true, screenPlay);
		}
		else if (action == 8)
		{
			cout << "Two ships are trapped inside an ancient Egyptian tomb.\n"
				"A big one(size = 2 * 2) and a small one. Both ships\n"
				"cannot move through walls.At any point of time you can\n"
				"move either the big or the small ship. The big ship can\n"
				"move or carry blocks of total size 6. The small ship can\n"
				"move or carry blocks of total size 2. you shall finish\n"
				"thr screen in a given time by reaching the exit\n"
				"point on screen with both ships.\n\n"
				"the keys are:\n"
				"to move left press                - a or A\n"
				"to move right press               - d or D\n"
				"to move up press                  - w or W\n"
				"to move left press                - x or X\n"
				"to Switched to the Big Ship press - b or B\n"
				"Switched to the small Ship press  - s or S\n";
		}
		else if (action == 9)
			cout << "Exiting the game";
	}
}

//void GameManager::runGame(int blockColor, int shipColor, int wallColor, int winningColor, std::string* fileName, char mode, bool runSpecificGame, int screenPlay)
//{
//	int possibleNextGame = GAME_NEED_TO_RUN;
//	int numLifes = START_LIFE;
//
//	if (mode == LOAD_MODE || mode == SILENT_MODE)
//	{
//
//	}
//	ofstream result(fileName[screenPlay].substr(0, 4) + ".result.txt");
//
//	while (possibleNextGame == GAME_NEED_TO_RUN || possibleNextGame == GAME_STOPED)
//	{
//		if (mode == LOAD_MODE || mode == SILENT_MODE)
//			possibleNextGame = runLoadGame(blockColor, shipColor, wallColor, winningColor, fileName[screenPlay], mode, numLifes, result);
//		else
//			possibleNextGame = runShipGame(blockColor, shipColor, wallColor, winningColor, fileName[screenPlay], mode, numLifes, result);
//
//		if (possibleNextGame == GAME_EXIT)
//			break;
//		else if (possibleNextGame == GAME_LOST)
//		{
//			--numLifes;
//
//			if (numLifes == 0)
//			{
//				clrscr();
//				cout << "you lost the game";
//			}
//			else
//				possibleNextGame = GAME_NEED_TO_RUN;
//		}
//		else if (possibleNextGame == GAME_WON)
//		{
//			screenPlay++;
//
//			if (!runSpecificGame && screenPlay == 3 || runSpecificGame)
//			{
//				clrscr();
//				cout << "YOU WON!!!";
//			}
//			else
//			{
//				possibleNextGame = GAME_NEED_TO_RUN;
//
//				if (mode != ' ')
//				{
//					result.close();
//					ofstream result(fileName[screenPlay].substr(0, 4) + ".result.txt");
//				}
//			}
//		}
//	}
//
//	result.close();
//}

void GameManager::runLoadGame(int blockColor, int shipColor, int wallColor, int winningColor, std::string* fileName, char mode)
{
	int gameStatus = GAME_NEED_TO_RUN, screenPlay = 0, timeStatus = -1;
	int numLifes = START_LIFE;
	ifstream recording, result;
	int firstPart, secondPart, thirdPart;
	bool diffResult = false;
	std::string line;

	recording.open(fileName[screenPlay].substr(0, 4) + ".steps.txt");
	result.open(fileName[screenPlay].substr(0, 4) + ".result.txt");

	while (gameStatus == GAME_NEED_TO_RUN || gameStatus == GAME_STOPED)
	{
		getline(result, line);
		std::istringstream lineStream(line);
		lineStream >> firstPart >> secondPart >> thirdPart; // Extract the two parts

		//playGame
		loadGame theGame;
		clrscr();
		theGame.setColors(blockColor, shipColor, wallColor, winningColor);
		theGame.init(fileName[screenPlay]);
		theGame.showMenu();
		gameStatus = theGame.run(mode, numLifes, recording, &timeStatus);
		
		//Comparison between a desired result and what happened
		if ((gameStatus == GAME_WON || gameStatus == GAME_LOST) &&
			(timeStatus != firstPart || gameStatus != secondPart))
		{
			diffResult = true;
		}

		if (gameStatus == GAME_EXIT)
		{
			break;
		}
		else if (gameStatus == GAME_LOST)
		{
			--numLifes;

			if (numLifes == 0)
			{
				clrscr();
				cout << "you lost the game";
			}
			else
				gameStatus = GAME_NEED_TO_RUN;
		}
		else if (gameStatus == GAME_WON)
		{
			recording.close();
			result.close();
			screenPlay++;

			if (screenPlay == 3)
			{
				clrscr();
				cout << "YOU WON!!!";
			}
			else
			{
				gameStatus = GAME_NEED_TO_RUN;
				recording.open(fileName[screenPlay].substr(0, 4) + ".steps.txt");
				result.open(fileName[screenPlay].substr(0, 4) + ".result.txt");
			}
		}
	}

	recording.close();
	result.close();

	clrscr();
	if (diffResult)
		cout << "result file is different than from result we got here";
	else
		cout << "same result file from before";
}


void GameManager::runShipGame(int blockColor, int shipColor, int wallColor, int winningColor, std::string* fileName, char mode, bool runSpecificGame, int screenPlay)
{
	int possibleNextGame = GAME_NEED_TO_RUN;
	int numLifes = START_LIFE;

	ofstream recording, result;
	
	if (mode == SAVE_MODE)
	{
		recording.open(fileName[screenPlay].substr(0, 4) + ".steps.txt");
		result.open(fileName[screenPlay].substr(0, 4) + ".result.txt");
	}
	
	while (possibleNextGame == GAME_NEED_TO_RUN || possibleNextGame == GAME_STOPED)
	{
		ShipsGame theGame;
		clrscr();
		theGame.setColors(blockColor, shipColor, wallColor, winningColor);
		theGame.init(fileName[screenPlay]);
		theGame.showMenu();
		possibleNextGame = theGame.run(mode, numLifes, result, recording);

		if (possibleNextGame == GAME_EXIT)
		{
			if (mode == SAVE_MODE)
			{
				result.close();
				recording.close();
			}
			break;
		}
		else if (possibleNextGame == GAME_LOST)
		{
			--numLifes;

			if (numLifes == 0)
			{
				if (mode == SAVE_MODE)
				{
					result.close();
					recording.close();
				}

				clrscr();
				cout << "you lost the game";
			}
			else
				possibleNextGame = GAME_NEED_TO_RUN;
		}
		else if (possibleNextGame == GAME_WON)
		{
			screenPlay++;

			if (!runSpecificGame && screenPlay == 3 || runSpecificGame)
			{
				clrscr();
				cout << "YOU WON!!!";
			}
			else
				possibleNextGame = GAME_NEED_TO_RUN;

			if (mode == SAVE_MODE)
			{
				result.close();
				recording.close();

				recording.open(fileName[screenPlay].substr(0, 4) + ".steps.txt");
				result.open(fileName[screenPlay].substr(0, 4) + ".result.txt");
			}
		}
	}
}











//
//void GameManager::runGame(int blockColor, int shipColor, int wallColor, int winningColor, std::string * fileName, char mode, bool runSpecificGame, int screenPlay)
//{
//	int possibleNextGame = GAME_NEED_TO_RUN;
//	int numLifes = START_LIFE;
//
//	if (mode == LOAD_MODE || mode == SILENT_MODE)
//	{
//
//	}
//	ofstream result(fileName[screenPlay].substr(0, 4) + ".result.txt");
//
//	while (possibleNextGame == GAME_NEED_TO_RUN || possibleNextGame == GAME_STOPED)
//	{
//		if (mode == LOAD_MODE || mode == SILENT_MODE)
//			possibleNextGame = runLoadGame(blockColor, shipColor, wallColor, winningColor, fileName[screenPlay], mode, numLifes, result);
//		else
//			possibleNextGame = runShipGame(blockColor, shipColor, wallColor, winningColor, fileName[screenPlay], mode, numLifes, result);
//
//		if (possibleNextGame == GAME_EXIT)
//			break;
//		else if (possibleNextGame == GAME_LOST)
//		{
//			--numLifes;
//
//			if (numLifes == 0)
//			{
//				clrscr();
//				cout << "you lost the game";
//			}
//			else
//				possibleNextGame = GAME_NEED_TO_RUN;
//		}
//		else if (possibleNextGame == GAME_WON)
//		{
//			screenPlay++;
//
//			if (!runSpecificGame && screenPlay == 3 || runSpecificGame)
//			{
//				clrscr();
//				cout << "YOU WON!!!";
//			}
//			else
//			{
//				possibleNextGame = GAME_NEED_TO_RUN;
//
//				if (mode != ' ')
//				{
//					result.close();
//					ofstream result(fileName[screenPlay].substr(0, 4) + ".result.txt");
//				}
//			}
//		}
//	}
//
//	result.close();
//}
//
//int GameManager::runLoadGame(int blockColor, int shipColor, int wallColor, int winningColor, std::string fileName, char mode, int numLifes, std::ofstream & result)
//{
//	int possibleNextGame;
//
//	ifstream recording;
//	recording.open(fileName.substr(0, 4) + ".steps.txt");
//
//	if (!recording.is_open())
//		std::cerr << "Failed to open file." << std::endl;
//
//	loadGame theGame;
//	clrscr();
//	theGame.setColors(blockColor, shipColor, wallColor, winningColor);
//	theGame.init(fileName);
//	theGame.showMenu();
//	possibleNextGame = theGame.run(mode, numLifes, result, recording);
//	recording.close();
//
//	return possibleNextGame;
//}
//
//int GameManager::runShipGame(int blockColor, int shipColor, int wallColor, int winningColor, std::string fileName, char mode, int numLifes, std::ofstream & result)
//{
//	int possibleNextGame;
//
//	ofstream recording(fileName.substr(0, 4) + ".steps.txt");
//	if (!recording.is_open())
//		std::cerr << "Failed to open file." << std::endl;
//
//	ShipsGame theGame;
//	clrscr();
//	theGame.setColors(blockColor, shipColor, wallColor, winningColor);
//	theGame.init(fileName);
//	theGame.showMenu();
//	possibleNextGame = theGame.run(mode, numLifes, result, recording);
//	recording.close();
//
//	return possibleNextGame;
//}
//
//int GameManager::getLastResult(std::string fileName)
//{
//	//can be max 3 lines in file (you ha
//	std::string LastResult[4]
//		ifstream result(fileName.substr(0, 4) + ".result.txt");
//	if (result.is_open()) {
//		std::string line;
//		while (std::getline(result, line)) {
//			std::cout << line << std::endl;
//		}
//		result.close();
//	}
//}
