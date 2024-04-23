﻿#ifndef SHIPS_GAMES_H
#define SHIPS_GAMES_H

class Ship;
class big_ship;

class ShipsGame
{
	Ship* smallShip;
	big_ship* bigShip;

	void drawBorder();
	void gameTime();
	void RemainingLifes();
public:
	void init();
	void run();
	void freeMemory();
};

#endif

