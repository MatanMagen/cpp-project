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
				ships[0].setBackgroundColor(shipColor);
			}
			else if (board[i][j] == '#') {
				ships[1].addPoint(j, i);
				ships[1].setBackgroundColor(shipColor);
			}
			else if (board[i][j] >= 'a' && board[i][j] <= 'c') {
				size_t block_index = board[i][j] - 'a';
				blocks[block_index].addPoint(j, i);
				blocks[block_index].setBackgroundColor(blockColor);
			}
			else if (board[i][j] == 'X') {
				exit_pos.set(j, i);
			}
		}
	}
}

void Board::show() {
	int color = 0;

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (board[i][j] == '@' || board[i][j] == '#')
				color = shipColor;
			else if (board[i][j] >= 'a' && board[i][j] <= 'c')
				color = blockColor;
			else if (board[i][j] == 'X')
				color = winningColor;
			else if (board[i][j] == 'W')
				color = wallColor;
			else
				color = 0;
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[color]);
			std::cout << board[i][j];
				//<< std::endl;
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
		std::cout << "\n";
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
	
	gotoxy(10, 22);
	std::cout << "The time Remaining is :";
	gotoxy(10, 23);
	std::cout << "The lifes Remaining is:";
}
