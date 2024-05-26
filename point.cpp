#include "point.h"

void Point::init(int x, int y)
{
	this->x = x;
	this->y = y;
	diff_x = 1;
	diff_y = 0;
}

void Point::draw(char ch, int backgroundColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
	gotoxy(x, y);
	cout << ch;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[0]);
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

	x += diff_x;
	if (x > GameConfig::GAME_WIDTH)
		x = 1;
	else if (x == -1)
		x = GameConfig::GAME_WIDTH;

	y += diff_y;
	if (y > GameConfig::GAME_HEIGHT + 3)
		y = 1;
	else if (y == -1)
		y = GameConfig::GAME_HEIGHT + 2;

}