#include "Player.h"
#include <iostream>

using std::cout;
using std::endl;

Player::Player() {}
Player::Player(string color, int money) : color(color), money(money) {}
Player::~Player() {}

//TODO: add number of houses per player condition 
bool Player::buyHouse(City c) {
	cout << "buying " << c.getName() << endl;
	int houseNumber = c.getHouses().size();
	int houseCost = c.getCost();
	if (houseNumber == 3) {
		cout << "Can't build in this city anymore." << endl;
	}
	else {
		if (money < houseCost) {
			cout << "You need " << houseCost << " elektros to buy a house here, but you only have " << money << endl;
		}
		else {
			cities.push_back(c);
			money -= houseCost;
			return true;
		}
	}
	return false;
}

void Player::buyResource(Resource r) {
	int resourceCost = r.getCost();
	if (money < resourceCost) {
		cout << "You need " << resourceCost << " elektros to buy this resource, but you only have " << money << endl;
	}
	else {
		resources[r.getType()] += 1;
		money -= resourceCost;
	}
}

void Player::buyPowerplantCard(PowerplantCard p, int cost) {
	if (money < cost) {
		cout << "You need " << cost << " elektros to buy this powerplant, but you only have " << money << endl;
	}
	else {
		powerplantCards.push_back(p);
		money -= cost;
	}
}