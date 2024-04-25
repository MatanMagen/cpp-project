#ifndef BOARD_H
#define BOARD_H

#include "Point.h"
#include "Ship.h"
#include "Block.h"
#include <iostream>
#include <cstring>

class Board {
	constexpr static size_t WIDTH = 80;
	constexpr static size_t HEIGHT = 25;
	constexpr static size_t NUM_SHIPS = 2;
	constexpr static size_t NUMBLOCKS = 1;
	// the original board that will be copied to the actual board
	char original_board[HEIGHT][WIDTH + 1] = {
		//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
			"W ##   @@                                                                      W", // 1
			"W ##                                                                           W", // 2
			"W                                                                              W", // 3
			"W                                                                              W", // 4
			"W                                                                              W", // 5
			"W                                                                              W", // 6
			"W                                                                              W", // 7
			"W                                                                              W", // 8
			"W                                                                              W", // 9
			"W                                                                              W", // 10
			"W                                                                              W", // 11
			"W                                                                              W", // 12
			"W                                              WWWWWWWWWWWWWW                  W", // 13
			"W                                              W            W                  W", // 14
			"W                                       W      b    W       WWWW               W", // 15
			"W                                       WWWWWWWWWWWWW          W               W", // 16
			"W                                                              W               W", // 17
			"W                                W            AAA       X      W               W", // 18
			"W                                WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW               W", // 19
			"W                                                                              W", // 20
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 21
			"W  The time Remaining is:                      The lifes Remaining is :        W", // 22
			"W                                                                              W", // 23
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"  // 24
	};
	// the actual board that will be modified
	char board[HEIGHT][WIDTH + 1];
	Ship ships[NUM_SHIPS];
	Block blocks[NUM_BLOCKS];
	Point legend_pos;
	Point exit_pos;

public:
	void init();
	void show();
	Ship& getships(int i) {
		return ships[i];
	}
	char getChar(Point pos);
};

#endif