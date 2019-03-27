#include "City.h"

void City::addHouse(House h) {
	houses.push_back(h);
	cost += 5; //Increment the cost for the next house in this city
}

void City::operator=(City c) {
	name = c.getName();
	regionName = c.getRegionName();
	for (auto house : c.getHouses()) {
		addHouse(house);
	}
	setCost(c.getCost());
}