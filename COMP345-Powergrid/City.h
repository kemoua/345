/**
	Represents a city.
*/
#pragma once
#include <string>
#include <vector>
#include "House.h"

using std::string;

class City {
public:
	City() {}
	City(string name) : name(name) {}
	string getName() const { return name; }
	void setName(string name) { this->name = name; }
	std::vector<House> getHouses() const { return houses; }
	int getCost() const { return cost; }
	void setCost(int p) { cost = p; }
	void addHouse(House h);
	void setRegionName(string name) { regionName = name; }
	string getRegionName() const { return regionName; }

	void operator = (City c);
	bool operator < (const City& c) const
	{
		return (name < c.getName());
	}

private:
	string name;
	string regionName;
	std::vector<House> houses;
	int cost = 10;
};