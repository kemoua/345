#pragma once
#include <string>
#include <vector>
#include <map>
#include "City.h"
#include "Resource.h"
#include "PowerplantCard.h"

using std::string;
using std::vector;
using std::map;

class Player {
public:
	Player();
	Player(string color, int elektro);
	~Player();

	string getColor() const { return color; }
	void setColor(string color) { this->color = color; }
	int getMoney() const { return money; }
	void setMoney(int money) { this->money = money; }
	map<string, int> getResource() const { return resources; }
	void setResource(Resource r, int q) { resources[r.getType()] = q; }

	void buyPowerplantCard(PowerplantCard p, int cost);
	void buyResource(Resource r);
	void buyHouse(City c);

private:
	string color;
	int money;
	map<string, int> resources;
	vector<City> cities;
	vector<PowerplantCard> powerplantCards;
};