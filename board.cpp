#include "board.h"

void Board::init() {
	std::memcpy(board, original_board, sizeof(original_board));
	for (int i = 0; i < HEIGHT - INFO_SIZE_HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (board[i][j] == '&') {
				legend_pos.set(j, i);
			}
			else if (board[i][j] == '@') {
				ships[0].addPoint(j, i);
			}
			else if (board[i][j] == '#') {
				ships[1].addPoint(j, i);
			}
			else if (board[i][j] >= 'a' && board[i][j] <= 'b') {
				size_t block_index = board[i][j] - 'a';
				blocks[block_index].addPoint(j, i);
			}
			else if (board[i][j] == 'X') {
				exit_pos.set(j, i);
			}
		}
	}
}

void Board::show() {
	for (int i = 0; i < HEIGHT; i++) {
		std::cout << board[i] << std::endl;
	}
}

