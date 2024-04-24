#ifndef BLOCK_H
#define BLOCK_H

#include "Point.h"

class Block
{
private:
	Point body[MAX_BlOCK_SIZE];
	int sizeBlock;
	char ch;
public:
	void init(Point& head, char ch, int size);
	void move(GameConfig::eKeys direction);
};

#endif


