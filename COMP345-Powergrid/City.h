/**
	Represents a city.
*/
#pragma once
#include <string>
#include <vector>
#include "House.h"

class City {
public:
	City() {}
	City(std::string name) : name(name) {}
	std::string getName() const { return name; }
	void setName(std::string name) { this->name = name; }
	std::vector<House> getHouses() const { return houses; }
	int getCost() const { return cost; }
	void setCost(int p) { cost = p; }
	void addHouse(House h);

private:
	std::string name;
	std::vector<House> houses;
	int cost = 10;
};