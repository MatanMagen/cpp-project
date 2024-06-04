#ifndef SHIPS_GAMES_H
#define SHIPS_GAMES_H

#include "gameConfig.h"
#include "ship.h"
#include "block.h"
#include "board.h"
using namespace std;

#define GAME_STOPED 0
#define GAME_LOST 1
#define GAME_WON 2

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
	void init(std::string fileName) {
		board.init(fileName);
	}
	void showMenu() {
		board.show();
	}
	void gameInfo(int* time, char ship, int numLifes);
	int run(int numLifes);
};

#endif
