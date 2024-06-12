#include "gameManager.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <cstring>
using std::string;
namespace fs = std::filesystem;
#include <fstream>
#include <conio.h> // for kbhit+getch
#include <Windows.h> // for Sleep and colors
#include "general.h"
#include "gameConfig.h"
#include "point.h"
#include "ship.h"
#include "shipsGame.h"

void GameManager::playGame(int argc, char* argv[])
{
	char mode;

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

	if (argv[1] == "-load" && argv[2] == "-silent")
	{
		mode = 's';
	}
	else if (argv[1] == "-load" && argv[2] != "-silent")
	{
		mode = 'l';
	}
	else if (argv[1] == "-save")
		mode = 'r'; //recording game
	else //playing regular game from the keyboard
		gameMenu(screens, numScreens);


}

void GameManager::runShipsGame(int blockColor, int shipColor, int wallColor, int winningColor, std::string* fileName)
{
	int screenPlay = 0;
	int possibleNextGame;
	int numLifes = START_LIFE;
	ofstream recording(fileName[screenPlay].substr(0, 4) + ".steps.txt");
	ofstream result(fileName[screenPlay].substr(0, 4) + ".result.txt");

	while (numLifes > 0 && screenPlay < 3)
	{
		ShipsGame theGame;
		clrscr();
		theGame.setColors(blockColor, shipColor, wallColor, winningColor);
		theGame.init(fileName[screenPlay]);
		theGame.showMenu();
		possibleNextGame = theGame.run(numLifes, result, recording);

		if (possibleNextGame == GAME_STOPED)
			break;
		else if (possibleNextGame == GAME_LOST)
		{
			recording << "minus life" << endl;
			--numLifes;
		}
		else if (possibleNextGame == GAME_WON)
		{
			recording << "new screen" << endl;
			screenPlay++;
		}

	}

	if (numLifes == 0)
	{
		clrscr();
		cout << "you lost the game";
	}

	if (screenPlay == 3)
	{
		clrscr();
		cout << "YOU WON!!!";
	}
	recording.close();
	result.close();

}

void GameManager::runSpecificGame(int blockColor, int shipColor, int wallColor, int winningColor, std::string fileName)
{
	bool possibleNextGame = true;
	int numLifes = START_LIFE;
	ofstream recording(fileName.substr(0, 4) + ".steps.txt");
	ofstream result(fileName.substr(0, 4) + ".result.txt");

	while (numLifes > 0 && possibleNextGame)
	{
		ShipsGame theGame;
		clrscr();
		theGame.setColors(blockColor, shipColor, wallColor, winningColor);
		theGame.init(fileName);
		theGame.showMenu();
		possibleNextGame = theGame.run(numLifes, result, recording);

		if (possibleNextGame == GAME_STOPED)
			break;
		else if (possibleNextGame == GAME_LOST)
		{
			recording << "minus life" << endl;
			--numLifes;
		}
		else if (possibleNextGame == GAME_WON)
		{
			clrscr();
			cout << "YOU WON!!!";
			break;
		}
	}

	if (numLifes == 0)
	{
		clrscr();
		cout << "you lost the game";
	}
	recording.close();
	result.close();

}

void GameManager::gameMenu(std::string* screens, int numScreens)
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

			runShipsGame(blockColor, shipColor, wallColor, winningColor, screens);
		}
		else if (action == 2)
		{
			int i = 0;

			cout << "Please select which screen you would like to play\n";

			for (int i = 0; i < 3; i++)
				std::cout << i + 1 << ". " << screens[i] << "\n";

			screenPlay = _getch() - '1';
			runSpecificGame(blockColor, shipColor, wallColor, winningColor, screens[screenPlay]);
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