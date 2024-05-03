#ifndef SHIPS_GAMES_H
#define SHIPS_GAMES_H

#include "gameConfig.h"
#include "Board.h"

class Ship;
class Block;
class Board;

class ShipsGame
{
	Board board;


public:
	void init() {
		board.init();
	}
	void showMenu() {
		board.show();
	}
	void gameTime(int* time);
	bool RemainingLifes(int* time);
	bool run();
	void freeMemory();
};

#endif
