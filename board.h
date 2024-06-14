#ifndef BOARD_H
#define BOARD_H
#include <string>
#include "Point.h"
#include "Ship.h"
#include "Block.h"
#include "gameConfig.h"
#include <conio.h>
#include <vector>
#include <fstream>

#define INFO_SIZE_HEIGHT 3

class Board {
	constexpr static size_t WIDTH = 80;
	constexpr static size_t HEIGHT = 25;
	constexpr static size_t NUM_SHIPS = 2;
	constexpr static size_t NUMBLOCKS = 1;
	// the original board that will be copied to the actual board
	char original_board[HEIGHT][WIDTH + 1];

	// the actual board that will be modified
	char board[HEIGHT][WIDTH + 1];
	Ship ships[NUM_SHIPS];
	std::vector<Block> blocks;
	Point legend_pos;
	Point exit_pos;
	int blockColor;
	int shipColor;
	int wallColor;
	int winningColor;
	char time[4];

public:
	bool readMap(std::string fileName);
	void init(std::string fileName);
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
	int getTime()
	{
		return std::stoi(time);
	}
	Ship& getships(int i) {
		return ships[i];
	}
	Block& getblock(char ch) {
		return blocks[ch - 'a'];
	}
	Point& getLegend() {
		return legend_pos;
	}
};

#endif