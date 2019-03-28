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

void testMap() {
	MapLoader loader = MapLoader();
	loader.loadMap("MapUSA.txt");
	Map m = Map(loader.getRegions(), loader.getCities(), loader.getConnections());
	loader.~MapLoader();
	cout << "List of cities with their connections: " << endl;
	cout << endl << "Connections list: " << endl;
	for (auto c : m.getConnections()) {
		cout << c.toString() << endl;
	}
}

void testHousesEtc() {
	//Houses, resources, money Test
	ResourceSetup rs = ResourceSetup();
	cout << "Resources on board: " << endl;
	for (auto i : rs.getResourcesOnBoard()) {
		cout << i.first << ": " << i.second << endl;
	}
	cout << "Lowest price for each resources: " << endl;
	for (auto i : rs.getCheapestPrices()) {
		cout << i.first << ": " << i.second << endl;
	}
	rs.removeResource("uranium", 1);
	rs.addResource("garbage", 5);
	rs.removeResource("coal", 3);
	cout << "Resources on board: " << endl;
	for (auto i : rs.getResourcesOnBoard()) {
		cout << i.first << ": " << i.second << endl;
	}
	cout << "Lowest price for each resources: " << endl;
	for (auto i : rs.getCheapestPrices()) {
		cout << i.first << ": " << i.second << endl;
	}
}

void testPowerPlantCards() {
	CardDriver cd = CardDriver();
	for (auto card : cd.getCards()) {
		cout << card.getNumber() << " ";
	}
	cout << endl;
	cout << "Cards on board:" << endl;
	for (auto card : cd.getCardsOnBoard()) {
		cout << card.getNumber() << " ";
	}
	cout << endl;
	int number = 0;
	while (true) {
		cout << "Buy powerplant: ";
		cin >> number;
		if (number == 99) { break; }
		if (cd.buyCard(number)) {
			for (auto card : cd.getCardsOnBoard()) {
				cout << card.getNumber() << " ";
			}
			cout << endl;
		}
		else {
			cout << "This powerplant number is not available." << endl;
		}
	}
}

int main()
{
	//uncomment test to run

	//testMap();
	//testPlayer();
	//testHousesEtc();
	//testPowerPlantCards();

	Game game = Game();
	game.start();
	while (true) {
		game.phase1();
		//game.phase2();
		//game.phase3();
		game.phase4();
	}
}