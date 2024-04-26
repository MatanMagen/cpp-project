#ifndef SHIP_H
#define SHIP_H

#include "point.h"

class Board;

class Ship {
	constexpr static size_t MAX_SHIP_SIZE = 4;
	Point pos[MAX_SHIP_SIZE];
	size_t size = 0;
	Board* board = nullptr; // pointer to the board
public:
	void setBoard(Board* board) {
		this->board = board;
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
	void move(GameConfig::eKeys direction, char ch, Board& board);
};

#endif