#include <math.h>
#include "ResourceSetup.h"
#include "Color.h"
#include "Resource.h"
#include <iostream>

using std::cout;
using std::endl;

ResourceSetup::ResourceSetup() {
	for (int i = 0; i < 6; i++) {
		houses[Color::getColor(i)] = 22;
	}

	resourcesTotal["coal"] = 24;
	resourcesTotal["oil"] = 24;
	resourcesTotal["garbage"] = 24;
	resourcesTotal["uranium"] = 12;

	resourcesOnBoard["coal"] = 24;
	resourcesOnBoard["oil"] = 18;
	resourcesOnBoard["garbage"] = 6;
	resourcesOnBoard["uranium"] = 2;

	money = 10000;
}

map<string, int> ResourceSetup::getCheapestPricePerResource() const{
	map<string, int> cheapestPrices;
	for (auto r : resourcesOnBoard) {
		string f = r.first;
		int s = r.second;
		if (f != "uranium") {
			cheapestPrices[f] = 9 - ceil(s / 3);
		}
		else {
			if (s < 5) {
				cheapestPrices[f] = 18 - 2 * s;
			}
			else {
				cheapestPrices[f] = 13 - s;
			}
		}
	}
	return cheapestPrices;
}