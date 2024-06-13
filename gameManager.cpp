#include "gameManager.h"

void GameManager::playGame(int argc, char* argv[])
{
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

	if (argc > 1)
	{
		if (strcmp(argv[1], "-load") == 0)
		{
			if (argc > 2 && strcmp(argv[2], "-silent") == 0)
				mode = SILENT_MODE;
			else
				mode = LOAD_MODE;
		}
		else if (strcmp(argv[1], "-save") == 0)
			mode = SAVE_MODE; //recording game
	}
	
	if(mode != LOAD_MODE && mode != SILENT_MODE) //playing regular game from the keyboard
		gameMenu(screens, numScreens, mode);
}

void GameManager::runShipsGame(int blockColor, int shipColor, int wallColor, int winningColor, std::string* fileName, char mode, bool runSpecificGame, int screenPlay)
{
	int possibleNextGame = GAME_NEED_TO_RUN;
	int numLifes = START_LIFE;
	ofstream recording;
	fstream result;

	if (mode == SAVE_MODE)
	{
		recording.open(fileName[screenPlay].substr(0, 4) + ".steps.txt");
	}

	result.open(fileName[screenPlay].substr(0, 4) + ".result.txt");

	while (numLifes > 0 && (possibleNextGame == GAME_NEED_TO_RUN || possibleNextGame == GAME_STOPED))
	{
		ShipsGame theGame;
		clrscr();
		theGame.setColors(blockColor, shipColor, wallColor, winningColor);
		theGame.init(fileName[screenPlay]);
		theGame.showMenu();
		possibleNextGame = theGame.run(mode, numLifes, result, recording);

		if (possibleNextGame == GAME_EXIT)
			break;
		else if (possibleNextGame == GAME_LOST)
		{
			recording << "minus life" << endl;
			--numLifes;

			if (numLifes == 0)
			{
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
				recording << "WON!!!" << endl;
				clrscr();
				cout << "YOU WON!!!";
			}
			else
			{
				recording << "won screen" << endl;
				if (mode == SAVE_MODE)
				{
					recording.close();
					recording.open(fileName[screenPlay].substr(0, 4) + ".steps.txt");
				}
				result.close();
				result.open(fileName[screenPlay].substr(0, 4) + ".result.txt");
				possibleNextGame = GAME_NEED_TO_RUN;
			}
		}
	}

	if (mode == SAVE_MODE)
	{
		recording.close();
	}
	result.close();

}

void GameManager::gameMenu(std::string* screens, int numScreens, char mode)
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

			runShipsGame(blockColor, shipColor, wallColor, winningColor, screens, mode, false, screenPlay);
		}
		else if (action == 2)
		{
			int i = 0;

			cout << "Please select which screen you would like to play\n";

			for (int i = 0; i < 3; i++)
				std::cout << i + 1 << ". " << screens[i] << "\n";

			screenPlay = _getch() - '1';
			runShipsGame(blockColor, shipColor, wallColor, winningColor, screens, mode, true, screenPlay);
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