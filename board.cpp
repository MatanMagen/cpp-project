#include "board.h"

bool Board::readMap(std::string fileName) {
	bool opend = true;
	ifstream file(fileName);

	if (!file.is_open()) {
		cerr << "Error opening file: " << fileName << endl;
		return false;
	}

	for (int i = 0; i < HEIGHT; ++i) {
		if (!file.getline(original_board[i], WIDTH + 1)) {
			cerr << "Error reading from file: " << fileName << endl;
			return false;
		}
	}

	if (!file.getline(time, 4)) {
		cerr << "Error reading from file: " << fileName << endl;
		return false;
	}

	file.close();
	return opend;
}

void Board::init(std::string fileName) {
	std::vector<Block> currBlocks(MAX_BLOCKS);

	if (!readMap(fileName))
		return;
	std::memcpy(board, original_board, sizeof(original_board));
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (board[i][j] == '&') {
				legend_pos.set(j, i);
			}
			else if (board[i][j] == '@') {
				ships[0].addPoint(j, i);
				ships[0].setShipType('@');
				ships[0].setMaxMove(MAX_MOVE_SMALL_SHIP);
				//ships[0].setBackgroundColor(shipColor);
			}
			else if (board[i][j] == '#') {
				ships[1].addPoint(j, i);
				ships[1].setShipType('#');
				ships[1].setMaxMove(MAX_MOVE_BIG_SHIP);
				//ships[1].setBackgroundColor(shipColor);
			}
			else if (board[i][j] >= 'a' && board[i][j] <= 'z') {
				size_t block_index = board[i][j] - 'a';
				currBlocks[block_index].addPoint(j, i);
				//blocks[block_index].setBackgroundColor(blockColor);
			}
			else if (board[i][j] == 'X') {
				exit_pos.set(j, i);
			}
		}
	}

	currBlocks.shrink_to_fit();
	blocks = currBlocks;	
}

void Board::show() {
	int color = 0;

	for (int i = 0; i < HEIGHT; i++) {
		std::cout << board[i] << std::endl;
	}

	gotoxy(legend_pos.getX() + 2, legend_pos.getY());
	std::cout << "The time Remaining is:";
	gotoxy(legend_pos.getX() + 2, legend_pos.getY() + 1);
	std::cout << "The lifes Remaining is:";
	gotoxy(legend_pos.getX() + 2, legend_pos.getY() + 2);
	std::cout << "The Active ship is:";
}
