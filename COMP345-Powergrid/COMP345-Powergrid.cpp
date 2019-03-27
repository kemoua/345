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

void part1() {
	//Map loading
	vector<string> maps = { "MapUSA.txt", "MapBad1.txt", "MapBad2.txt" };
	MapLoader loader;
	int input;
	bool valid = false;
	int i = 0;
	cout << "Load map:" << endl;
	for (auto map : maps) {
		cout << i << ": " << map << endl;
		i++;
	}
	//Load and check if map file is valid
	while (!valid) {
		loader = MapLoader();
		cout << "Enter choice: ";
		cin >> input;
		if (cin.fail() || input < 0 || input > 2) {
			cout << "Please enter a valid choice." << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		else if (loader.loadMap(maps.at(input))) {
			valid = true;
		}
		else {
			loader.~MapLoader();
		}
		cin.clear();
	}
	Map m = Map(loader.getRegions(), loader.getCities(), loader.getConnections());
	loader.~MapLoader();

	//Resources and cards loading
	ResourceSetup rs = ResourceSetup();
	CardDriver cd = CardDriver();

	//Players
	vector<Player> players;
	Color colors;
	cout << "Enter number of players: ";
	cin >> input;
	while (cin.fail() || input < 2 || input > 6) {
		cout << "Please enter number between 2 and 6." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Enter number of players: ";
		cin >> input;
	}
	cout << "selected " << input << " players" << endl;
	//For each player, assign color, elektro quantity, houses, summary card;
	SummaryCard summaryCard = SummaryCard();
	for (int i = 0; i < input; i++) {
		string currentColor = colors.getColor(i);
		Player p = Player(currentColor, 50);
		for (int j = 0; j < 22; j++) {
			p.addHouse(House(currentColor));
		}
		p.addSummaryCard(summaryCard);
		players.push_back(p);
	}
	for (auto p : players) {
		cout << p.getColor() << ", Number of houses: " << p.getHouses().size() << endl;
		cout << p.getSummaryCard().getPlayOrder() << endl;
	}
	cout << endl;

	//Select Regions
	int count = 0;
	string regionChoice;
	vector<string> regionsChosen;
	int maxNumberRegions = 0;
	switch (input) {
	case 2: maxNumberRegions = 3;
		break;
	case 3: maxNumberRegions = 3;
		break;
	case 4: maxNumberRegions = 4;
		break;
	case 5: maxNumberRegions = 5;
		break;
	case 6: maxNumberRegions = 5;
	}
	cout << "You need to select " << maxNumberRegions << " regions." << endl;
	while (count < maxNumberRegions) {
		cout << "Please select a region between: ";
		if (count == 0) {
			for (auto rg : m.getRegions()) {
				cout << rg.getName() << " ";
			}
		}
		else {
			for (auto r : m.getRegionAdjacency(regionChoice)) {
				if (!(std::find(regionsChosen.begin(), regionsChosen.end(), r) != regionsChosen.end())) {
					cout << r << " ";
				}
			}
		}
		cout << endl;
		cin >> regionChoice;
		//
		// I'm assuming the user enters correct values. You can add tests for the user input here.
		// They would be similar to the tests used above for the input of the map choice and the number of players.
		//
		regionsChosen.push_back(regionChoice);
		count++;
	}


	system("pause");
}

int main()
{
	//uncomment test to run

	//testMap();
	//testPlayer();
	//testHousesEtc();
	//testPowerPlantCards();

	part1();
}