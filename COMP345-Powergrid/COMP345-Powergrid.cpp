// COMP345-Powergrid.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <string>
#include <Windows.h>
#include <algorithm>
#include "Player.h"
#include "Map.h"
#include "MapLoader.h"
#include "Color.h"
#include "ResourceSetup.h"
#include "CardDriver.h"
#include "Game.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;

int main()
{
	//uncomment phase to run

	Game game = Game();
	game.start();
	while (true) {
		game.phase1();
		game.phase2();
		game.phase3();
		game.phase4();
		game.phase5();
	}
}