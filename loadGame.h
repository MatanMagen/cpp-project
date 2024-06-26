#ifndef LOAD_GAMES_H
#define LOAD_GAMES_H

#include "gameConfig.h"
#include "ship.h"
#include "block.h"
#include "board.h"
#include "abs_game.h"
#include <fstream>
#include <sstream>

using namespace std;
using std::string;

class Ship;
class Block;
class Board;

class loadGame :public abs_Game
{

public:
	int run(char mode, int numLifes, std::ifstream& recording, int *timeStatus);
};

#endif
