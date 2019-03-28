/**
	Class that sets up the number of resources, houses and money available at the start of the game.
	Handles the resources on the board.
	Keeps track of the minimal cost of each resource.
*/
#pragma once
#include <map>
#include "House.h"
#include "Resource.h"
#include "Money.h"

using std::map;

class ResourceSetup {
public:
	ResourceSetup();

	map<string, int> getHouses() const { return houses; }
	map<string, int> getResourcesTotal() const { return resourcesTotal; }
	map<string, int> getResourcesOnBoard() const { return resourcesOnBoard; }
	Money getMoney() const { return money; }

	void updateCheapestPrices();
	void updateCheapestPrice(string resourceType);
	map<string, int> getCheapestPrices() const { return cheapestPrices; }

	Resource getNextResource(string type);
	void addResource(string type, int qty);
	void removeResource(string type, int qty);
	int getPrice(string resourceType, int qty) const;

private:
	map<string, int> houses;
	map<string, int> resourcesTotal;
	map<string, int> resourcesOnBoard;
	map<string, int> cheapestPrices;
	Money money;
};