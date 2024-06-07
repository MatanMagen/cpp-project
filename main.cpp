#include"main.h"

int main(int argc, char* argv[])
{	
	GameManager game;
	game.playGame(argc, argv);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
	gotoxy(0, GameConfig::GAME_HEIGHT + 4);
}
