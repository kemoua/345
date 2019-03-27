/**
	Represents the map of the game.
	Contains regions, cities and their connections.
*/
#pragma once
#include <vector>
#include <map>
#include  "Region.h"
#include "City.h"
#include "Connection.h"

using std::vector;

class Map {
public:
	Map() {}
	Map(vector<Region> regions, vector<City> cities, vector<Connection> connections);
	void createRegion(std::string name);
	void createCity(City city);
	void createConnection(City startCity, City endCity, int cost);
	void addCityToRegion(City city, Region region);

	vector<Region> getRegions() const { return regions;  }
	vector<City> getCities() const { return cities; }
	vector<Connection> getConnections() const { return connections; }
	vector<string> getRegionAdjacency(string regionName) const;
	vector<Region> getAvailableRegions() const { return availableRegions; }
	vector<City> getAvailableCities() const { return availableCities; }

	void setAvailableRegionsAndCities(vector<string> regionsChoice);
	void displayConnectionsForCity(City c) const;

private:
	vector<Region> regions;
	vector<City> cities;
	vector<Connection> connections;
	vector<Region> availableRegions;
	vector<City> availableCities;
};