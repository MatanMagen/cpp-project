#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H

#define START_TIME 250
#define START_LIFE 3
#define NUM_BLOCKS 3
#define BIG_SHIP_SIZE 4
#define SMALL_SHIP_SIZE 2
#define MAX_MOVE_BIG_SHIP 6
#define MAX_MOVE_SMALL_SHIP 2
#define BLOCK_COLOR 9604
#define SHIP_COLOR 7072
#define WALLS_COLOR 1509
#define WINNING_COLOR 6967

class GameConfig
{
public:
	enum class eKeys {
		LOWER_LEFT = 'a', LEFT = 'A', LOWER_RIGHT = 'd', RIGHT = 'D',
		LOWER_UP = 'w', UP = 'W', LOWER_DOWN = 'x', DOWN = 'X', ESC = 27, SWAP_BIG_LOWER = 'b',
		SWAP_BIG = 'B', SWAP_SMALL_LOWER = 's', SWAP_SMALL = 'S', PAUSE = 'p', EXIT = 57
	};

	static constexpr int GAME_WIDTH = 80;
	static constexpr int GAME_HEIGHT = 18;

	static constexpr int MIN_X = 0;
	static constexpr int MIN_Y = 0;

	static const int COLORS[];
	static const int NUM_OF_COLORS;
};
#endif