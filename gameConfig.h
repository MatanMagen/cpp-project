#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H

class GameConfig
{
public:
	enum class eKeys {LOWER_LEFT = 'a', LEFT = 'A', LOWER_RIGHT = 'd', RIGHT = 'D',
		LOWER_UP = 'w', UP = 'W', LOWER_DOWN = 'x', DOWN = 'X', ESC = 27, SWAP_BIG_LOWER = 'b',
		SWAP_BIG = 'B', SWAP_SMALL_LOWER = 's', SWAP_SMALL = 'S',PAUSE = 'p' };
	static constexpr int GAME_WIDTH = 80;
	static constexpr int GAME_HEIGHT = 18;

	static constexpr int MIN_X = 10;
	static constexpr int MIN_Y = 3;

	static const int COLORS[];
	static const int NUM_OF_COLORS;
};
#endif