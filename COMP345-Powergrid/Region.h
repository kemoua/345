#pragma once
#include <string>
#include <vector>
#include "City.h"

using std::string;
using std::vector;

class Region {
public:
	Region() {}
	Region(string name) : name(name) {}
	string getName() const { return name; }
	void setName(string name) { this->name = name; }
	void addCity(City city) { cities.push_back(city); }
	vector<City> getCities() const { return cities; }
private:
	string name;
	vector<City> cities;
};