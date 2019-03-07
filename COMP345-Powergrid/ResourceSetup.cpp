#include <math.h>
#include "ResourceSetup.h"
#include "Color.h"
#include "Resource.h"
#include <iostream>

using std::cout;
using std::endl;

ResourceSetup::ResourceSetup() {
	for (int i = 0; i < 6; i++) {
		houses[Color::getColor(i)] = 22;
	}

	resourcesTotal["coal"] = 24;
	resourcesTotal["oil"] = 24;
	resourcesTotal["garbage"] = 24;
	resourcesTotal["uranium"] = 12;

	resourcesOnBoard["coal"] = 24;
	resourcesOnBoard["oil"] = 18;
	resourcesOnBoard["garbage"] = 6;
	resourcesOnBoard["uranium"] = 2;

	updateCheapestPrices();
	money = 10000;
}

void ResourceSetup::updateCheapestPrices() {
	for (auto r : resourcesOnBoard) {
		string f = r.first;
		int s = r.second;
		if (f != "uranium") {
			cheapestPrices[f] = 9 - ceil(s / 3);
		}
		else {
			if (s < 5) {
				cheapestPrices[f] = 18 - 2 * s;
			}
			else {
				cheapestPrices[f] = 13 - s;
			}
		}
	}
}

void ResourceSetup::updateCheapestPrice(string resourceType) {
	int qtyOnBoard = resourcesOnBoard[resourceType];
	if (resourceType != "uranium") {
		cheapestPrices[resourceType] = 9 - ceil(qtyOnBoard / 3);
	}
	else {
		if (qtyOnBoard < 5) {
			cheapestPrices[resourceType] = 18 - 2 * qtyOnBoard;
		}
		else {
			cheapestPrices[resourceType] = 13 - qtyOnBoard;
		}
	}
}

Resource ResourceSetup::getNextResource(string resourceType) {
	int cost = cheapestPrices[resourceType];
	return Resource(resourceType, cost);
}

void ResourceSetup::addResource(string type, int qty) {
	resourcesOnBoard[type] += qty;
	updateCheapestPrice(type);
}

void ResourceSetup::removeResource(string type, int qty) {
	resourcesOnBoard[type] -= qty;
	updateCheapestPrice(type);
}
