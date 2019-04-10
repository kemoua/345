// COMP345-Powergrid.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "GameDriver.h"

int main()
{
	GameDriver* game = new GameDriver();
	game->run();
	delete game;
}