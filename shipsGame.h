#ifndef SHIPS_GAMES_H
#define SHIPS_GAMES_H

#include "gameConfig.h"
#include "ship.h"
#include "block.h"
#include "board.h"
#include "abs_game.h"
#include <fstream>
using namespace std;
using std::string;

class Ship;
class Block;
class Board;

class ShipsGame :public abs_Game
{

public:
	int run(char mode, int numLifes, std::fstream& result, std::fstream& recording);
};

#endif
