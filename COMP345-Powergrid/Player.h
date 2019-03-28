/**
	Represents a player.
	Handles actions that the player can make, such as buying houses or buying resources.
*/
#pragma once
#include <string>
#include <vector>
#include <map>
#include "City.h"
#include "House.h"
#include "SummaryCard.h"
#include "Resource.h"
#include "PowerplantCard.h"

using std::string;
using std::vector;
using std::map;

class Player {
public:
	Player();
	Player(string color, int money);
	~Player();

	string getColor() const { return color; }
	void setColor(string color) { this->color = color; }
	int getMoney() const { return money; }
	void setMoney(int money) { this->money = money; }
	map<string, int> getResource() const { return resources; }
	void setResource(Resource r, int q) { resources[r.getType()] = q; }
	vector<PowerplantCard> getPowerplantCards() const { return powerplantCards; }
	vector<City> getCities() const { return cities; }
	vector<House> getHouses() const { return houses; }
	SummaryCard getSummaryCard() const { return summaryCard; }
	int getHighestPowerplantCardNumber() const { return highestPowerplantNumber; }

	void addSummaryCard(SummaryCard card) { summaryCard = card; }
	void addHouse(House h) { houses.push_back(h); }
	void buyPowerplantCard(PowerplantCard p, int cost);
	void buyResource(Resource r);
	bool buyHouse(City c, int connectionPrice);
	void updatePowerplantCards(vector<PowerplantCard> pcs);

	void displayResources() const;
	void getPayment(int payment) { money += payment; }

	bool operator < (const Player& p) const
	{
		if (cities.size() == p.getCities().size()) {
			return highestPowerplantNumber < p.getHighestPowerplantCardNumber();
		}
		return (cities.size() < p.getCities().size());
	}

	bool operator == (const Player& p) const
	{
		return (color == p.getColor());
	}

private:
	string color;
	int money;
	int highestPowerplantNumber;
	map<string, int> resources;
	vector<House> houses;
	vector<City> cities;
	vector<PowerplantCard> powerplantCards;
	SummaryCard summaryCard;
};