#ifndef BLOCK_H
#define BLOCK_H

#include "Point.h"
#include "stdbool.h"

class Board;

class Block {
	constexpr static size_t MAX_BlOCK_SIZE = 6;
	Point pos[MAX_BlOCK_SIZE];
	size_t size = 0;
	Board* board = nullptr; // pointer to the board
	int backgroundColor;

public:
	void setBackgroundColor(int backgroundColor) {
		this->backgroundColor = backgroundColor;
	}
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
	void editPoint(int i, Point newPos) {
		pos[i] = newPos;
	}
	bool move(GameConfig::eKeys direction, char ch, Board& board, bool isCarried, int maxMove);
	bool ishitObject(GameConfig::eKeys direction, char ch, Board& board, bool* hitBlock, char* whichBlockHit);
	bool toFall(GameConfig::eKeys direction, char ch, Board& board, bool isCarried);
	bool isKilledShip(char ch, Board& board);
};

#endif


