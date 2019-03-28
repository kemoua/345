#include <math.h>
#include "ResourceSetup.h"
#include "Color.h"
#include "Resource.h"
#include <iostream>

using std::cout;
using std::endl;

//Initial setup
ResourceSetup::ResourceSetup() {
	for (int i = 0; i < 6; i++) {
		houses[Color::getColor(i)] = 22;
	}

	resourcesTotal["coal"] = 0;
	resourcesTotal["oil"] = 6;
	resourcesTotal["garbage"] = 18;
	resourcesTotal["uranium"] = 10;

	resourcesOnBoard["coal"] = 24;
	resourcesOnBoard["oil"] = 18;
	resourcesOnBoard["garbage"] = 6;
	resourcesOnBoard["uranium"] = 2;

	updateCheapestPrices();
	money = 10000;
}

//Update cheapest price available for each type of resources
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

//Return the next available resource of a specific type
Resource ResourceSetup::getNextResource(string resourceType) {
	int cost = cheapestPrices[resourceType];
	return Resource(resourceType, cost);
}

//Add resource on the board
void ResourceSetup::addResource(string type, int qty) {
	for (int i = 0; i < qty; i++) {
		if (resourcesTotal[type] == 0) {
			break;
		}
		resourcesOnBoard[type]++;
		resourcesTotal[type]--;
	}
	updateCheapestPrice(type);
}

//Remove resource from the board
void ResourceSetup::removeResource(string type, int qty) {
	resourcesOnBoard[type] -= qty;
	updateCheapestPrice(type);
}

//Add resource to the total
void ResourceSetup::addResourceTotal(string type, int qty) {
	resourcesTotal[type] += qty;
}

//Remove resource from total
int ResourceSetup::removeResourceTotal(string type, int qty) {
	int removed = 0;
	for (int i = 0; i < qty; i++) {
		if (resourcesTotal[type] == 0) {
			removed = i;
			break;
		}
		else {
			resourcesTotal[type]--;
		}
	}
	return (qty - removed);
}

//Return the minimum total cost of a quantity of a resource
int ResourceSetup::getPrice(string resourceType, int qty) const{
	int totalPrice = 0;
	for (auto r : resourcesOnBoard) {
		string type = r.first;
		int qtyOnBoard = r.second;
		if (type == resourceType) {
			for (int i = 0; i < qty; i++) {
				if (resourceType != "uranium") {
					totalPrice += 9 - ceil((qtyOnBoard - i) / 3);
				}
				else {
					if (qtyOnBoard < 5) {
						totalPrice += 18 - 2 * (qtyOnBoard - i);
					}
					else {
						totalPrice += 13 - (qtyOnBoard - i);
					}
				}
			}
			break;
		}
	}
	return totalPrice;
}

void ResourceSetup::resupply(int nP, int step) {
	switch (nP) {
	case 2:
		switch (step) {
		case 1:
			addResource("coal", 3);
			addResource("oil", 2);
			addResource("garbage", 1);
			addResource("uranium", 1);
			break;
		case 2:
			addResource("coal", 4);
			addResource("oil", 2);
			addResource("garbage", 2);
			addResource("uranium", 1);
			break;
		case 3:
			addResource("coal", 3);
			addResource("oil", 4);
			addResource("garbage", 3);
			addResource("uranium", 1);
			break;
		}
		break;
	case 3:
		switch (step) {
		case 1:
			addResource("coal", 4);
			addResource("oil", 2);
			addResource("garbage", 1);
			addResource("uranium", 1);
			break;
		case 2:
			addResource("coal", 5);
			addResource("oil", 3);
			addResource("garbage", 2);
			addResource("uranium", 1);
			break;
		case 3:
			addResource("coal", 3);
			addResource("oil", 4);
			addResource("garbage", 3);
			addResource("uranium", 1);
			break;
		}
		break;
	case 4:
		switch (step) {
		case 1:
			addResource("coal", 5);
			addResource("oil", 3);
			addResource("garbage", 2);
			addResource("uranium", 1);
			break;
		case 2:
			addResource("coal", 6);
			addResource("oil", 4);
			addResource("garbage", 3);
			addResource("uranium", 2);
			break;
		case 3:
			addResource("coal", 4);
			addResource("oil", 5);
			addResource("garbage", 4);
			addResource("uranium", 2);
			break;
		}
		break;
	case 5:
		switch (step) {
		case 1:
			addResource("coal", 5);
			addResource("oil", 4);
			addResource("garbage", 3);
			addResource("uranium", 2);
			break;
		case 2:
			addResource("coal", 7);
			addResource("oil", 5);
			addResource("garbage", 3);
			addResource("uranium", 3);
			break;
		case 3:
			addResource("coal", 5);
			addResource("oil", 6);
			addResource("garbage", 5);
			addResource("uranium", 2);
			break;
		}
		break;
	case 6:
		switch (step) {
		case 1:
			addResource("coal", 7);
			addResource("oil", 5);
			addResource("garbage", 3);
			addResource("uranium", 2);
			break;
		case 2:
			addResource("coal", 9);
			addResource("oil", 6);
			addResource("garbage", 5);
			addResource("uranium", 3);
			break;
		case 3:
			addResource("coal", 6);
			addResource("oil", 7);
			addResource("garbage", 6);
			addResource("uranium", 3);
			break;
		}
		break;
	}
}