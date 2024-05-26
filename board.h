#ifndef BOARD_H
#define BOARD_H

#include "Point.h"
#include "Ship.h"
#include "Block.h"
#include "gameConfig.h"
#include <conio.h>

#define INFO_SIZE_HEIGHT 3

class Board {
	constexpr static size_t WIDTH = 80;
	constexpr static size_t HEIGHT = 25;
	constexpr static size_t NUM_SHIPS = 2;
	constexpr static size_t NUMBLOCKS = 1;
	// the original board that will be copied to the actual board
	char original_board[HEIGHT][WIDTH + 1] = {
		//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
			"W ## W @@        b                                                             W", // 1
			"W ## W           W   W                                                         W", // 2
			"W    W           W   W                                                         W", // 3
			"W    WWWWWWWWWWWWW   WWWWWWWWWWWWWWWW   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 4
			"W                                                                              W", // 5
			"W                                                                              W", // 6
			"W                                                                              W", // 7
			"W                                                                              W", // 8
			"W                                                                              W", // 9
			"W                                                                              W", // 10
			"W                                                                              W", // 11
			"W                                                                              W", // 12
			"W                                              WWWWWWWWWWWWWWWWW               W", // 13
			"W                                              W               W               W", // 14
			"W                                       W      c    W          WWWW            W", // 15
			"W                                       WWWWWWWWWWWWW             W            W", // 16
			"W                                             a                   W            W", // 17
			"W                                W            aa           W  X   W            W", // 18
			"W                                WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW            W", // 19
			"W                                                                              W", // 20
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 21
			"W  &                                                                           W", // 22
			"W                                                                              W", // 23
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"  // 24
	};
	// the actual board that will be modified
	char board[HEIGHT][WIDTH + 1];
	Ship ships[NUM_SHIPS];
	Block blocks[NUM_BLOCKS];
	Point legend_pos;
	Point exit_pos;
	int blockColor;
	int shipColor;
	int wallColor;
	int winningColor;

public:
	void init();
	void show();
	void setColors(int blockColor, int shipColor, int wallColor, int winningColor)
	{
		this->blockColor = blockColor;
		this->shipColor = shipColor;
		this->wallColor = wallColor;
		this->winningColor = winningColor;
	}
	char(&getBoard())[HEIGHT][WIDTH + 1]{
		return board;
	}
		Ship& getships(int i) {
		return ships[i];
	}
	Block& getblock(char ch) {
		return blocks[ch - 'a'];
	}
};

#endif