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
vector<City> Map::getConnectionsForCity(City city) const {
	vector<City> connectedCities;
	string cityName = city.getName();
	int index = 1;
	for (auto c : connections) {
		if (cityName == c.getStartCity().getName()) {
			cout << c.getEndCity().getName() << " (connection cost: " << c.getCost() << ") " << std::endl;
			connectedCities.push_back(c.getEndCity());
		}
		else if (cityName == c.getEndCity().getName()) {
			cout << c.getStartCity().getName() << " (connection cost: " << c.getCost() << ") " << std::endl;
			connectedCities.push_back(c.getStartCity());
		}
		index++;
	}
	sort(connectedCities.begin(), connectedCities.end());
	return connectedCities;
}

vector<string> Map::getRegionAdjacency(vector<string> regionsName) const {
	vector<string> adj;
	for (auto regionName : regionsName) {
		for (auto c : connections) {
			if (c.getStartCity().getRegionName() == regionName) {
				adj.push_back(c.getEndCity().getRegionName());
			}
			if (c.getEndCity().getRegionName() == regionName) {
				adj.push_back(c.getStartCity().getRegionName());
			}
		}
	}
	std::sort(adj.begin(), adj.end());
	for (auto regionName : regionsName) {
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
	}
	return adj;
}

void Map::setAvailableRegionsAndCities(vector<string> regionsChoice) {
	for (auto regionName : regionsChoice) {
		for (auto region : regions) {
			if (region.getName() == regionName) {
				availableRegions.push_back(region);
				for (auto city : region.getCities()) {
					availableCities.push_back(city);
				}
			}
		}
	}
}

void Map::updateAvailableCities(vector<City> cities) {
	availableCities.clear();
	availableCities = cities;
}

int Map::getConnectionCost(City c1, City c2) const {
	int cost = -1;
	for (auto c : connections) {
		if (c.getStartCity().getName() == c1.getName() && c.getEndCity().getName() == c2.getName()) {
			cost = c.getCost();
			break;
		}
		if (c.getStartCity().getName() == c2.getName() && c.getEndCity().getName() == c1.getName()) {
			cost = c.getCost();
			break;
		}
	}
	return cost;
}