#ifndef BLOCK_H
#define BLOCK_H

#include "Point.h"

class Board;

class Block {
	constexpr static size_t MAX_BlOCK_SIZE = 6;
	Point pos[MAX_BlOCK_SIZE];
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
};

#endif


