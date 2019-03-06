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

	map<string, int> getCheapestPricePerResource() const;

private:
	map<string, int> houses;
	map<string, int> resourcesTotal;
	map<string, int> resourcesOnBoard;
	Money money;
};