// COMP345-Powergrid.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include "Player.h"
#include "Map.h"
#include "MapLoader.h"
#include "Color.h"
#include "ResourceSetup.h"

using std::cout;
using std::endl;
using std::vector;

int main()
{
	//Map
	MapLoader loader = MapLoader();
	loader.loadMap("MapUSA.txt");
	Map m = Map(loader.getRegions(), loader.getCities(), loader.getConnections());
	loader.~MapLoader();

	//Houses, resources, money
	ResourceSetup rs = ResourceSetup();
	cout << "Resources on board: " << endl;
	for (auto i : rs.getResourcesOnBoard()) {
		cout << i.first << ": " << i.second << endl;
	}
	cout << "Lowest price for each resources: " << endl;
	for (auto i : rs.getCheapestPricePerResource()) {
		cout << i.first << ": " << i.second << endl;
	}
}