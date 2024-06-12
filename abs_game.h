#ifndef ABS_GAME_H
#define ABS_GAME_H

#include "gameConfig.h"
#include "ship.h"
#include "block.h"
#include "board.h"
using namespace std;
using std::string;

#define GAME_STOPED 0
#define GAME_LOST 1
#define GAME_WON 2

class Board;

class abs_Game
{
	Board board;
	string name;

public:
	void setColors(int blockColor, int shipColor, int wallColor, int winningColor) {
		board.setColors(blockColor, shipColor, wallColor, winningColor);
	}
	void init(std::string fileName) {
		board.init(fileName);
		name = fileName;
	}
	void showMenu() {
		board.show();
	}
	virtual void gameInfo(int* time, char ship, int numLifes);
	virtual int runStep(int keyPlay, int numLifes, std::ofstream& result, std::ofstream& recording);
	virtual int status(int keyPlay, int numLifes, std::ofstream& result, std::ofstream& recording);
	virtual void abstract()const = 0;

};

#endif