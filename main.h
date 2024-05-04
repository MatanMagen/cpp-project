#ifndef MAIN_H
#define MAIN_H

#include <conio.h> // for kbhit+getch
#include <iostream>
#include <Windows.h> // for Sleep and colors
using namespace std;

#include "general.h"
#include "gameConfig.h"
#include "point.h"
#include "ship.h"
#include "shipsGame.h"

void runShipsGame();
void menu();
void RemainingLifes(int numLifes);

#endif