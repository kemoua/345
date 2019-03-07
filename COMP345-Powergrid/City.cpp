#include "City.h"

void City::addHouse(House h) {
	houses.push_back(h);
	cost += 5; //Increment the cost for the next house in this city
}