#pragma once
#include <string>
#include <vector>
#include  "Region.h"
#include "City.h"
#include "Connection.h"

using namespace::std;

class MapLoader {
public:
	MapLoader() {}
	~MapLoader() {}
	void loadMap(std::string filename);
	vector<Region> getRegions() { return regions; }
	vector<City> getCities() { return cities; }
	vector<Connection> getConnections() { return connections; }

private:
	vector<Region> regions;
	vector<City> cities;
	vector<Connection> connections;
};