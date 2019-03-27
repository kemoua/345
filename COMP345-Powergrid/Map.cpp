#include <iostream>
#include <map>
#include <algorithm>
#include "Map.h"

using std::cout;

Map::Map(vector<Region> regions, vector<City> cities, vector<Connection> connections) :
	regions(regions), cities(cities), connections(connections) {}

void Map::createRegion(std::string name) {
	regions.push_back(Region(name));
}

void Map::createCity(City city) {
	cities.push_back(city);
}

void Map::createConnection(City startCity, City endCity, int cost) {
	connections.push_back(Connection(startCity, endCity, cost));
}

void Map::addCityToRegion(City city, Region region) {
	region.addCity(city);
}

//Display for a city the list of cities connected to it and the costs associated to the connections
void Map::displayConnectionsForCity(City city) const {
	string cityName = city.getName();
	cout << cityName << ": ";
	for (auto c : connections) {
		if (cityName == c.getStartCity().getName()) {
			cout << c.getEndCity().getName() << " (" << c.getCost() << ") ";
		}
		else if (cityName == c.getEndCity().getName()) {
			cout << c.getStartCity().getName() << " (" << c.getCost() << ") ";
		}
	}
	cout << std::endl;
}

vector<string> Map::getRegionAdjacency(string regionName) const {
	vector<string> adj;
	for (auto c : connections) {
		if (c.getStartCity().getRegionName() == regionName) {
			adj.push_back(c.getEndCity().getRegionName());
		}
		if (c.getEndCity().getRegionName() == regionName) {
			adj.push_back(c.getStartCity().getRegionName());
		}
	}
	std::sort(adj.begin(), adj.end());
	string current = "";
	for (auto it = adj.begin(); it != adj.end();) {
		if (*it == regionName || *it == current) {
			it = adj.erase(it);
		}
		else {
			current = *it;
			++it;
		}
	}
	return adj;
}