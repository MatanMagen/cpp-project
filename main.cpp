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

	theGame.init();
	theGame.run();
	theGame.freeMemory();
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
