#include "Map.h"

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