#ifndef __GAME_MANAGER_H
#define __GAME_MANAGER_H

#include <filesystem>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <cstring>
using std::string;
namespace fs = std::filesystem;
#include <conio.h> // for kbhit+getch
#include <Windows.h> // for Sleep and colors
#include "general.h"
#include "gameConfig.h"
#include "point.h"
#include "ship.h"
#include "shipsGame.h"

class GameManager
{
	
public:
	void runShipsGame(int blockColor, int shipColor, int wallColor, int winningColor, std::string* fileName);
	void runSpecificGame(int blockColor, int shipColor, int wallColor, int winningColor, std::string fileName);
	void gameMenu(std::string* screens, int numScreens);
	void playGame(int argc, char* argv[]);
};


#endif