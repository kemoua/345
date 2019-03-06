// COMP345-Powergrid.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include "Player.h"
#include "Map.h"
#include "MapLoader.h"
#include "Color.h"

using std::cout;
using std::endl;
using std::vector;

int main()
{
	MapLoader loader = MapLoader();
	loader.loadMap("MapUSA.txt");
	Map m = Map(loader.getRegions(), loader.getCities(), loader.getConnections());
	loader.~MapLoader();
}