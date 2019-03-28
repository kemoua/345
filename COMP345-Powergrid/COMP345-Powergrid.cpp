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
	for (auto c : m.getCities()) {
		m.displayConnectionsForCity(c);
	}
	cout << endl << "Connections list: " << endl;
	for (auto c : m.getConnections()) {
		cout << c.toString() << endl;
	}
}

void testPlayer() {
	Player p1 = Player("blue", 50);
	Player p2 = Player("red", 50);
	City c1 = City("c1");
	City c2 = City("c2");
	Resource coal1 = Resource("coal", 1);
	Resource uranium14 = Resource("uranium", 14);
	Resource garbage14 = Resource("garbage", 8);
	PowerplantCard pc1 = PowerplantCard(1, "coal", 2, 1);
	PowerplantCard pc2 = PowerplantCard(18, "uranium", 1, 3);
	PowerplantCard pc3 = PowerplantCard(7, "oil", 1, 3);
	// Test buying houses
	if (p1.buyHouse(c1)) {
		c1.addHouse(p1.getColor());
	}
	if (p2.buyHouse(c2)) {
		c2.addHouse(p2.getColor());
	}
	if (p1.buyHouse(c2)) {
		c2.addHouse(p1.getColor());
	}
	cout << "p1 cities: " << endl;
	for (auto r : p1.getCities()) {
		cout << r.getName() << " ";
	}
	cout << endl << "p2 cities: " << endl;
	for (auto r : p2.getCities()) {
		cout << r.getName() << " ";
	}
	cout << endl << "Number of houses in c1: " << c1.getHouses().size() << endl;
	cout << "Number of houses in c2: " << c2.getHouses().size() << endl;
	cout << "p1 money: " << p1.getMoney() << endl;
	cout << "p2 money: " << p2.getMoney() << endl;
	// Test buying resources
	p1.buyResource(coal1);
	p1.buyResource(uranium14);
	p1.buyResource(garbage14);
	cout << "p1 resources: " << endl;
	for (auto r : p1.getResource()) {
		cout << r.first << ": " << r.second << endl;
	}
	cout << "p2 resources: " << endl;
	for (auto r : p2.getResource()) {
		cout << r.first << ": " << r.second << endl;
	}
	cout << "p1 money: " << p1.getMoney() << endl;
	cout << "p2 money: " << p2.getMoney() << endl;
	//Test buying powerplant cards
	p1.buyPowerplantCard(pc1, pc1.getNumber());
	p1.buyPowerplantCard(pc2, pc2.getNumber());
	p2.buyPowerplantCard(pc2, pc2.getNumber());
	p2.buyPowerplantCard(pc3, pc3.getNumber());
	cout << "p1 powerplants: " << endl;
	for (auto r : p1.getPowerplantCards()) {
		cout << r.getNumber() << " ";
	}
	cout << endl << "p2 powerplants: " << endl;
	for (auto r : p2.getPowerplantCards()) {
		cout << r.getNumber() << " ";
	}
	cout << endl << "p1 money: " << p1.getMoney() << endl;
	cout << "p2 money: " << p2.getMoney() << endl;
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