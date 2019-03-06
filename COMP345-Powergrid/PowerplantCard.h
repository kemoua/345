#pragma once
#include <vector>
#include "Resource.h"

using std::vector;

class PowerplantCard {
public:
	PowerplantCard() {}
	PowerplantCard(int number, vector<Resource> resources, int cities) : number(number), resources(resources), cities(cities) {};

private:
	int number;
	vector<Resource> resources;
	int cities;
};