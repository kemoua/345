#pragma once
#include <string>
#include "City.h"

using std::string;

class Connection {
public:
	Connection() {}
	Connection(City startCity, City endCity, int cost);
	
	City getStartCity() const { return startCity; }
	void setStartCity(City startCity) { this->startCity = startCity; }
	City getEndCity() const { return endCity; }
	void setEndCity(City endCity) { this->endCity = endCity; }
	int getCost() const { return cost; }
	void setStartCity(int cost) { this->cost = cost; }
	string toString() const;


private:
	City startCity;
	City endCity;
	int cost;
};