
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "MapLoader.h"

using namespace std;

bool testMap(vector<Region> regions, vector<City> cities, std::map<string, int> connectionsPerCity) {
	//check that there are 6 regions and that each regions has 7 cities
	if (regions.size() != 6) {
		cout << "Not enough regions." << endl;
		return false;
	}
	for (auto region : regions) {
		if (region.getCities().size() != 7) {
			cout << "Not enough cities per region." << endl;
			return false;
		}
	}

	//Check that every city has at least one connection
	for (auto city : cities) {
		if (connectionsPerCity[city.getName()] == 0) {
			cout << "At least one city has no connections." << endl;
			return false;
		}
	}
	return true;
}

bool MapLoader::loadMap(std::string filename) {
	//Try to read the txt file of the map
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

		//Handle the first part of the file, delimited by '// Connection', which represents the list of cities with their region
		//The format in the file is: Region City
		while (!input.eof())
		{
			input >> regionName >> cityName;
			if (regionName == "//") {
				regions.push_back(r);
				break;
			}
			City c = City(cityName);
			if (regionName != currentRegion) {
				if (currentRegion != "") {
					regions.push_back(r);
				}
				r = Region(regionName);
				currentRegion = regionName;
			}
			c.setRegionName(r.getName());
			r.addCity(c);
			cities.push_back(c);

		}

		//Handle the second part of the file, which represents the connections
		//The format in the file is: City City Cost
		while (!input.eof())
		{
			City startCity;
			City endCity;
			input >> startCityName >> endCityName >> cost;
			for (auto city : cities) {
				if (city.getName() == startCityName) {
					startCity = city;
				}
				if (city.getName() == endCityName) {
					endCity = city;
				}
			}
			connections.push_back(Connection(startCity, endCity, cost));
			connectionsPerCity[startCityName] += 1;
			connectionsPerCity[endCityName] += 1;
		}
		
		//Once everything is loaded, test if the map is valid
		if (!testMap(regions, cities, connectionsPerCity)) { //Map is invalid if there is a city with no connections
			cout << "Invalid Map" << endl;
			return false;
		}

		input.close();
		return true;
	}
}
