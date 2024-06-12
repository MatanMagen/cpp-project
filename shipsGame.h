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

#define GAME_STOPED 0
#define GAME_LOST 1
#define GAME_WON 2
#define GAME_NEED_TO_RUN 3
#define GAME_EXIT 4

class Ship;
class Block;
class Board;

class ShipsGame :public abs_Game
{

public:
	int run(char mode, int numLifes, std::ofstream& result, std::ofstream& recording);
};

#endif
