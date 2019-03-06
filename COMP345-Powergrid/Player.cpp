#include "Player.h"
#include <iostream>

using std::cout;
using std::endl;

Player::Player() {}
Player::Player(string color, int money) : color(color), money(money) {}
Player::~Player() {}

//TODO: add number of houses per player condition 
void Player::buyHouse(City c) {
	int houseNumber = c.getHouses().size();
	if (houseNumber == 3) {
		cout << "Can't build in this city anymore." << endl;
	}
	else {
		if (money < c.getCost()) {
			cout << "You need " << c.getCost() << " elektros to buy a house here, but you only have " << money << endl;
		}
		else {
			cities.push_back(c);
			c.addHouse(House(color));
			money -= c.getCost();
		}
	}
}

void Player::buyResource(Resource r) {
	if (money < r.getCost()) {
		cout << "You need " << r.getCost() << " elektros to buy this resource, but you only have " << money << endl;
	}
	else {
		resources[r] += 1;
		money -= r.getCost();
	}
}

void Player::buyPowerplantCard(PowerplantCard p, int cost) {
	powerplantCards.push_back(p);
	money -= cost;
}