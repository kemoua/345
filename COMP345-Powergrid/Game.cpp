#include <iostream>
#include <map>
#include <string>
#include <Windows.h>
#include <algorithm>
#include "Game.h"
#include "MapLoader.h"
#include "CardDriver.h"
#include "Color.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;

void Game::start() {
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
	gameMap = Map(loader.getRegions(), loader.getCities(), loader.getConnections());
	loader.~MapLoader();

	//Resources and cards loading
	gameResources = ResourceSetup();
	gameCards = CardDriver();

	//Players
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
		gamePlayers.push_back(p);
	}
	for (auto p : gamePlayers) {
		cout << p.getColor() << ", number of houses: " << p.getHouses().size();
		cout << ", elektro: " << p.getMoney() << endl;
		p.displayResources(); //display nothing since the player has no resources at the start of the game
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
			for (auto rg : gameMap.getRegions()) {
				cout << rg.getName() << " ";
			}
		}
		else {
			for (auto r : gameMap.getRegionAdjacency(regionsChosen)) {
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
	gameMap.setAvailableRegionsAndCities(regionsChosen);
	//Display available regions and cities for players
	cout << "Regions available: ";
	for (auto region : gameMap.getAvailableRegions()) {
		cout << region.getName() << " ";
	}
	cout << endl;
	cout << "Cities available: ";
	for (auto city : gameMap.getAvailableCities()) {
		cout << city.getName() << " ";
	}
	cout << endl;
}