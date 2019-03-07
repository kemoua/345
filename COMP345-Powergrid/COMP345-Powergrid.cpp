// COMP345-Powergrid.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include "Player.h"
#include "Map.h"
#include "MapLoader.h"
#include "Color.h"
#include "ResourceSetup.h"
#include "CardDriver.h"

using std::cout;
using std::endl;
using std::vector;

int main()
{
	//Map
	/*MapLoader loader = MapLoader();
	loader.loadMap("MapUSA.txt");
	Map m = Map(loader.getRegions(), loader.getCities(), loader.getConnections());
	loader.~MapLoader();*/

	//Houses, resources, money
	/*ResourceSetup rs = ResourceSetup();
	cout << "Resources on board: " << endl;
	for (auto i : rs.getResourcesOnBoard()) {
		cout << i.first << ": " << i.second << endl;
	}
	cout << "Lowest price for each resources: " << endl;
	for (auto i : rs.getCheapestPrices()) {
		cout << i.first << ": " << i.second << endl;
	}*/

	//Powerplant Cards
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