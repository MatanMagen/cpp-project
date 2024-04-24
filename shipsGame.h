#ifndef SHIPS_GAMES_H
#define SHIPS_GAMES_H

#include "gameConfig.h"

class Ship;
class big_ship;

class ShipsGame
{
	Ship* smallShip;
	big_ship* bigShip;
	//Block* block1;
	//Block* block2;

	void drawBorder();
	void gameTime(int* time);
	void RemainingLifes();
public:
	void init();
	void run();
	void freeMemory();
};

#endif
