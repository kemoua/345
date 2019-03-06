
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "MapLoader.h"

using namespace std;

bool testMap(vector<City> cities, std::map<string, int> connectionsPerCity) {
	for (auto city : cities) {
		if (connectionsPerCity[city.getName()] == 0) {
			return false;
		}
	}
	return true;
}

void MapLoader::loadMap(std::string filename) {
	ifstream input(filename);

	if (input.fail())
	{
		cout << "File does not exist" << endl;
		cout << "Exit program" << endl;
	}
	else {
		string line, cityName, regionName, startCityName, endCityName;
		int cost;
		string currentRegion = "";
		Region r;
		std::map<string, int> connectionsPerCity;

		while (!input.eof())
		{
			input >> regionName >> cityName;
			if (regionName == "//") {
				regions.push_back(r);
				break;
			}
			City c = City(cityName);
			cities.push_back(City(cityName));
			if (regionName != currentRegion) {
				if (currentRegion != "") {
					regions.push_back(r);
				}
				r = Region(regionName);
				currentRegion = regionName;
			}
			r.addCity(c);
		}

		while (!input.eof())
		{
			input >> startCityName >> endCityName >> cost;
			connections.push_back(Connection(City(startCityName), City(endCityName), cost));
			connectionsPerCity[startCityName] += 1;
			connectionsPerCity[endCityName] += 1;
		}
		
		if (!testMap(cities, connectionsPerCity)) {
			cout << "Invalid Map" << endl;
		}

		input.close();
	}
}
