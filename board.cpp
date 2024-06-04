#include "board.h"
#include <fstream>

bool Board::readMap(std::string fileName) {
	//"map.txt"
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

	file.close();
	return opend;
}

void Board::init(std::string fileName) {
	if (!readMap(fileName))
		return;
	std::memcpy(board, original_board, sizeof(original_board));
	for (int i = 0; i < HEIGHT ; i++) {
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
			else if (board[i][j] >= 'a' && board[i][j] <= 'c') {
				size_t block_index = board[i][j] - 'a';
				blocks[block_index].addPoint(j, i);
				//blocks[block_index].setBackgroundColor(blockColor);
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
		std::cout << board[i] << std::endl;
	}

	//for (int i = 0; i < HEIGHT; i++) {
	//	for (int j = 0; j < WIDTH; j++) {
	//		if (board[i][j] == '@' || board[i][j] == '#')
	//			color = shipColor;
	//		else if (board[i][j] >= 'a' && board[i][j] <= 'c')
	//			color = blockColor;
	//		else if (board[i][j] == 'X')
	//			color = winningColor;
	//		else if (board[i][j] == 'W')
	//			color = wallColor;
	//		else
	//			color = GameConfig::COLORS[0];
	//		
	//		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
	//		std::cout << board[i][j];
	//		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), NO_COLOR);
	//	}

	//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
	//	std::cout << "\n";
	//}

	gotoxy(legend_pos.getX() + 2, legend_pos.getY());
	std::cout << "The time Remaining is:";
	gotoxy(legend_pos.getX() + 2, legend_pos.getY() + 1);
	std::cout << "The lifes Remaining is:";
	gotoxy(legend_pos.getX() + 2, legend_pos.getY() + 2);
	std::cout << "The Active ship is:";
}
