#include "Player.h"
#include <iostream>
#include <algorithm>
#include "AggressivePlayer.h"
#include "ModeratePlayer.h"
#include "EnvironmentalistPlayer.h"
#include "HumanPlayer.h"

using std::cout;
using std::endl;

Player::Player() {}
Player::Player(string color, int money) : color(color), money(money), highestPowerplantNumber(0) {}
Player::~Player() {}

//TODO: add number of houses per player condition 
bool Player::buyHouse(City c, int connectionPrice) {
	cout << "buying " << c.getName() << endl;
	int houseNumber = c.getHouses().size();
	int houseCost = c.getCost() + connectionPrice;
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
		if (p.getNumber() > highestPowerplantNumber) {
			highestPowerplantNumber = p.getNumber();
		}
		money -= cost;
	}
}

void Player::displayResources() const {
	for (auto r : getResource()) {
		cout << r.first << ": " << r.second << endl;
	}
}

bool comparePowerplantCards(PowerplantCard& p1, PowerplantCard& p2) {
	if (p1.getNumber() > p2.getNumber()) {
		return true;
	}
	else {
		return false;
	}
}

void Player::updatePowerplantCards(vector<PowerplantCard> pcs) {
	powerplantCards.clear();
	powerplantCards = pcs;
}

bool Player::makeAuction(vector<PowerplantCard> *pcs) {
	int choice = 0;
	while (choice != 1 and choice != 2) {
		cout << "Player " << color << " with " << money << " elektro choose action:" << endl;
		cout << "1: Pass" << endl;
		cout << "2: Auction" << endl;
		int strategyChoice = executeAuctionStrategy(pcs);
		//If human player, asks for choice
		if (strategyChoice == 99) {
			//Display the choice for each other strategy
			Player *p = new Player("dummy", money);
			p->setStrategy(new AggressivePlayer());
			strategyChoice = p->executeAuctionStrategy(pcs);
			cout << "Aggressive strategy is to ";
			if (strategyChoice == 0) {
				cout << "pass." << endl;
			}
			else {
				cout << "auction for card " << strategyChoice << endl;
			}
			p->deleteStrategy();
			p->setStrategy(new ModeratePlayer());
			strategyChoice = p->executeAuctionStrategy(pcs);
			cout << "Moderate strategy is to ";
			if (strategyChoice == 0) {
				cout << "pass." << endl;
			}
			else {
				cout << "auction for card " << strategyChoice << endl;
			}
			p->deleteStrategy();
			p->setStrategy(new EnvironmentalistPlayer());
			strategyChoice = p->executeAuctionStrategy(pcs);
			cout << "Environmentalist strategy is to ";
			if (strategyChoice == 0) {
				cout << "pass." << endl;
			}
			else {
				cout << "auction for card " << strategyChoice << endl;
			}
			delete p;
			std::cin >> choice;
		}
		else {
			//Choice depends on strategy
			choice = strategyChoice == 0 ? 1 : 2;
		}
		if (choice == 1) {
			return Pass();
		}
		if (choice == 2) {
			return Auction();
		}

	}
}