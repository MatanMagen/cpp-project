#ifndef SHIP_H
#define SHIP_H

#include "point.h"

class Board;

#define SHIP_FINISH 0
#define SHIP_DIED 1
#define SHIP_CAN_PLAY 2

class Ship {
	constexpr static size_t MAX_SHIP_SIZE = 4;
	Point pos[MAX_SHIP_SIZE];
	size_t size = 0;
	Board* board = nullptr; // pointer to the board
	int backgroundColor;
	char shipType;
	int maxMove;

public:
	void setBackgroundColor(int backgroundColor) {
		this->backgroundColor = backgroundColor;
	}
	void setBoard(Board* board) {
		this->board = board;
	}
	void setShipType(char ch) {
		this->shipType = ch;
	}
	void setMaxMove(int i) {
		this->maxMove = i;
	}
	void addPoint(int x, int y) {
		pos[size++].set(x, y);
	}
	size_t getSize() const {
		return size;
	}
	Point getPos(size_t i) const {
		return pos[i];
	}
	int move(GameConfig::eKeys direction, Board& board);
};

#endif