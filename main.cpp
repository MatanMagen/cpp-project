#include <conio.h> // for kbhit+getch
#include <iostream>
#include <Windows.h> // for Sleep and colors
using namespace std;

#include "general.h"
#include "gameConfig.h"
#include "point.h"
#include "ship.h"
#include "shipsGame.h"

// part 1
void testKbhitAndGetch();
void movingStar();
// part 2
void movingStarInBoard();
void drawBorder();
// part 3
void movingStarInBoardSomewhere();
void drawBorderSomewhere();
// part 4 - with class Point
void movingStarInBoardSomewhereWithPoint();
// part 6 - moving snake
void snakeTester();
// part 7 - many snakes!
void testShipsGame();
int menu();

int main()
{
	//testKbhitAndGetch();
	//movingStar();
	//movingStarInBoard();
	//movingStarInBoardSomewhere();
	//movingStarInBoardSomewhereWithPoint();
	//snakeTester();
	testShipsGame();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
	gotoxy(0, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 2);
}

void testShipsGame()
{
	ShipsGame theGame;

	if (menu() == 1)
	{
		theGame.init();
		theGame.run();
		theGame.freeMemory();
	}
	
}

int menu()
{
	int action = 0;
	Point point[GameConfig::GAME_WIDTH][GameConfig::GAME_HEIGHT];

	while (action != 1 && action != 9)
	{
		cout << "Please select the desired action from the following menu:\n";
		cout << "(1) Start a new game\n(8) Present instructions and keys\n(9) EXIT\n";
		cin >> action;

		if (action == 1)
		{
			clrscr();
			return 1;
		}
		else if (action == 8)
		{
			cout << "Two ships are trapped inside an ancient Egyptian tomb.\n"
				"A big one(size = 2 * 2) and a small one. Both ships\n"
				"cannot move through walls.At any point of time you can\n"
				"move either the big or the small ship. The big ship can\n"
				"move or carry blocks of total size 6. The small ship can\n"
				"move or carry blocks of total size 2. you shall finish\n"
				"thr screen in a given time by reaching the exit\n"
				"point on screen with both ships.\n\n"
				"the keys are:\n"
				"to move left press                - a or A\n"
				"to move right press               - d or D\n"
				"to move up press                  - w or W\n"
				"to move left press                - x or X\n"
				"to Switched to the Big Ship press - b or B\n"
				"Switched to the small Ship press  - s or S\n";
		}

		else if (action == 9)
		{
			cout << "Exiting the game";
			exit(1);
		}
	}
	
	return action;
}

//void testKbhitAndGetch()
//{
//	while (true)
//	{
//		cout << "Waiting for key\n";
//		if (_kbhit())
//		{
//			char pressedChar = _getch();
//			cout << pressedChar << " key was pressed\n";
//
//		}
//		cout << "another iteration\n";
//		Sleep(1000);
//	}
//}
//
//void movingStar()
//{
//	int x = 1, y = 1;
//
//	while (!_kbhit() || _getch() != 27)
//	{
//		gotoxy(x, y);
//		cout << "*";
//		Sleep(500);
//		gotoxy(x, y);
//		cout << " ";
//
//		++x;
//		if (x == 80)
//			x = 1;
//
//		++y;
//		if (y == 20)
//			y = 1;
//
//	}
//}
//
//void movingStarInBoard()
//{
//	drawBorder();
//	int x = 1, y = 1;
//
//	while (!_kbhit() || _getch() != 27)
//	{
//		gotoxy(x, y);
//		cout << "*";
//		Sleep(500);
//		gotoxy(x, y);
//		cout << " ";
//
//		++x;
//		if (x > GameConfig::GAME_WIDTH)
//			x = 1;
//
//		++y;
//		if (y > GameConfig::GAME_HEIGHT)
//			y = 1;
//
//	}
//}
//
//void drawBorder()
//{
//	for (int col = 0; col <= GameConfig::GAME_WIDTH + 1; col++)
//	{
//		gotoxy(col, 0);
//		cout << "-";
//
//		gotoxy(col, GameConfig::GAME_HEIGHT + 1);
//		cout << "-";
//	}
//
//	for (int row = 0; row <= GameConfig::GAME_HEIGHT + 1; row++)
//	{
//		gotoxy(0, row);
//		cout << "|";
//
//		gotoxy(GameConfig::GAME_WIDTH + 1, row);
//		cout << "|";
//	}
//}
//
//void movingStarInBoardSomewhere()
//{
//	drawBorderSomewhere();
//	int x = GameConfig::MIN_X, y = GameConfig::MIN_Y;
//
//	while (!_kbhit() || _getch() != 27)
//	{
//		gotoxy(x, y);
//		cout << "*";
//		Sleep(500);
//		gotoxy(x, y);
//		cout << " ";
//
//		++x;
//		if (x == GameConfig::GAME_WIDTH + GameConfig::MIN_X)
//			x = GameConfig::MIN_X;
//
//		++y;
//		if (y == GameConfig::GAME_HEIGHT + GameConfig::MIN_Y)
//			y = GameConfig::MIN_Y;
//
//	}
//}
//
//void movingStarInBoardSomewhereWithPoint()
//{
//	drawBorderSomewhere();
//	Point p;
//	p.init(1, 1);
//
//	while (true)
//	{
//		int keyPressed = 0;
//		if (_kbhit())
//		{
//			keyPressed = _getch();
//			if (keyPressed == (int)GameConfig::eKeys::ESC)
//				break;
//		}
//		p.draw('*', 120);
//		Sleep(500);
//		p.draw(' ', FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
//
//		p.move((GameConfig::eKeys)keyPressed);
//	}
//}
//void drawBorderSomewhere()
//{
//	for (int col = GameConfig::MIN_X; col < GameConfig::GAME_WIDTH + GameConfig::MIN_X; col++)
//	{
//		gotoxy(col, GameConfig::MIN_Y - 1);
//		cout << "-";
//
//		gotoxy(col, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y);
//		cout << "-";
//	}
//
//	for (int row = GameConfig::MIN_Y - 1; row <= GameConfig::GAME_HEIGHT + GameConfig::MIN_Y; row++)
//	{
//		gotoxy(GameConfig::MIN_X - 1, row);
//		cout << "|";
//
//		gotoxy(GameConfig::GAME_WIDTH + GameConfig::MIN_X, row);
//		cout << "|";
//	}
//}

//void snakeTester()
//{
//	drawBorderSomewhere();
//	//int x = GameConfig::MIN_X, y = GameConfig::MIN_Y;
//	Ship s;
//	Point head;
//	head.init(2, 2);
//	s.init(head, '#', GameConfig::COLORS[1]);
//
//	while (true)
//	{
//		int keyPressed = 0;
//		if (_kbhit())
//		{
//			keyPressed = _getch();
//			if (keyPressed == (int)GameConfig::eKeys::ESC)
//				break;
//		}
//		s.move((GameConfig::eKeys)keyPressed);
//		Sleep(500);
//	}
//}
