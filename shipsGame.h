#ifndef SHIPS_GAMES_H
#define SHIPS_GAMES_H

#include "gameConfig.h"
#include "ship.h"
#include "block.h"
#include "board.h"
using namespace std;

class Ship;
class Block;
class Board;

class ShipsGame
{
	Board board;

public:
	void setColors(int blockColor, int shipColor, int wallColor, int winningColor) {
		board.setColors(blockColor, shipColor, wallColor, winningColor);
	}
	void init() {
		board.init();
	}
	void showMenu() {
		board.show();
	}
	void gameInfo(int* time, char ship);
	bool run();
};

#endif
