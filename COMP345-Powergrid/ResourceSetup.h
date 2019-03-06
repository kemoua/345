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
	map<string, int> getResources() const { return resources; }
	Money getMoney() const { return money; }

private:
	map<string, int> houses;
	map<string, int> resources;
	Money money;
};