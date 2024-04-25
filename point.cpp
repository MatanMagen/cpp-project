#include "point.h"
#include "gameConfig.h"
#include "general.h"

#include <iostream>
#include <Windows.h>
#include <stdbool.h>
using namespace std;

void Point::init(int x, int y)
{
	this->x = x;
	this->y = y;
	diff_x = 1;
	diff_y = 0;
}

void Point::draw(char ch, int backcolor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backcolor);
	gotoxy(x + GameConfig::MIN_X - 1, y + GameConfig::MIN_Y - 1);
	cout << ch;
}

void Point::move(GameConfig::eKeys key)
{
	switch (key)
	{
	case GameConfig::eKeys::LEFT:
		diff_x = -1;
		diff_y = 0;
		break;
	case GameConfig::eKeys::RIGHT:
		diff_x = 1;
		diff_y = 0;
		break;
	case GameConfig::eKeys::UP:
		diff_x = 0;
		diff_y = -1;
		break;
	case GameConfig::eKeys::DOWN:
		diff_x = 0;
		diff_y = 1;
		break;
	case GameConfig::eKeys::LOWER_LEFT:
		diff_x = -1;
		diff_y = 0;
		break;
	case GameConfig::eKeys::LOWER_RIGHT:
		diff_x = 1;
		diff_y = 0;
		break;
	case GameConfig::eKeys::LOWER_UP:
		diff_x = 0;
		diff_y = -1;
		break;
	case GameConfig::eKeys::LOWER_DOWN:
		diff_x = 0;
		diff_y = 1;
		break;
	}

	if (!isCharacterAtPosition((x + diff_x) % GameConfig::GAME_WIDTH, (y + diff_y) % GameConfig::GAME_HEIGHT, 'W'))
	{
		x += diff_x;
		if (x > GameConfig::GAME_WIDTH)
			x = 1;
		else if (x == 0)
			x = GameConfig::GAME_WIDTH;

		y += diff_y;
		if (y > GameConfig::GAME_HEIGHT)
			y = 1;
		else if (y == 0)
			y = GameConfig::GAME_HEIGHT;
	}
}

bool Point::isCharacterAtPosition(int x, int y, char expectedChar) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole, &info);
	COORD pos = { short(x), short(y) };
	DWORD read;
	CHAR_INFO buffer;
	if (!ReadConsoleOutput(hConsole, &buffer, { 1, 1 }, pos, &info.srWindow)) {
		// Error handling
		return false;
	}
	// Check if there is a character at the specified position
	return buffer.Char.AsciiChar == expectedChar;
}

