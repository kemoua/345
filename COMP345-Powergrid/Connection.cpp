#include "Connection.h"
#include <string>

Connection::Connection(City startCity, City endCity, int cost) :
	startCity(startCity), endCity(endCity), cost(cost) {}

string Connection::toString() const {
	return startCity.getName() + " " + endCity.getName() + " " + std::to_string(cost);
}