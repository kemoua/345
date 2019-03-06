#include "City.h"

void City::addHouse(House h) {
	houses.push_back(h);
	cost += 5;
}