#ifndef SHIPS_GAMES_H
#define SHIPS_GAMES_H

#include "gameConfig.h"
#include "Board.h"

#include "ship.h"
#include "general.h"
#include "block.h"
#include "board.h"

#include <conio.h>
#include <Windows.h>


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
	void gameTime(int* time);
	bool RemainingLifes(int* time);
	bool run();
	void freeMemory();
};

#endif
