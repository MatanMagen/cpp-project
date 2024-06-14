#ifndef __GAME_MANAGER_H
#define __GAME_MANAGER_H

#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;
#include "shipsGame.h"
#include "loadGame.h"
#include "gameConfig.h"
#include <sstream>

class GameManager
{

public:
	void runLoadGame(int blockColor, int shipColor, int wallColor, int winningColor, std::string* fileName, char mode);
	void runShipGame(int blockColor, int shipColor, int wallColor, int winningColor, std::string* fileName, char mode, bool runSpecificGame, int screenPlay);
	//void runGame(int blockColor, int shipColor, int wallColor, int winningColor, std::string* fileName, char mode, bool runSpecificGame, int screenPlay);
	void menu(std::string* screens, int numScreens, char mode);
	void playGame(int argc, char* argv[]);
};


#endif