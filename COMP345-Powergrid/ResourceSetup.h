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

private:
	map<string, int> houses;
	map<string, int> resourcesTotal;
	map<string, int> resourcesOnBoard;
	map<string, int> cheapestPrices;
	Money money;
};