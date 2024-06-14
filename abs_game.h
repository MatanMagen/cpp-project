#ifndef ABS_GAME_H
#define ABS_GAME_H

#include "gameConfig.h"
#include "ship.h"
#include "block.h"
#include "board.h"
using namespace std;
using std::string;
#include <fstream>
#include <iostream>
#include <string>

#define GAME_STOPED 0
#define GAME_LOST 1
#define GAME_WON 2
#define GAME_NEED_TO_RUN 3
#define GAME_EXIT 4

class Board;

class abs_Game
{
	Board board;
	string name;
	int time;

public:
	void setColors(int blockColor, int shipColor, int wallColor, int winningColor) {
		board.setColors(blockColor, shipColor, wallColor, winningColor);
	}
	void init(std::string fileName) {
		board.init(fileName);
		name = fileName;
		time = board.getTime();
	}
	void showMenu() {
		board.show();
	}
	virtual int getTime()
	{
		return time;
	}

	virtual void gameInfo(char ship, int numLifes);
	virtual int runStep(int keyPlay, int lastKey, char* lastShip, int lastStatus, int numLifes, char mode);
	virtual char status(int keyPlay, int lastKey, char lastShip, int lastStatus, int numLifes, char mode, int* statusGame);
	virtual int resultGame(char mode, int numLifes, int shipStatus, std::ofstream& result);

};
#endif