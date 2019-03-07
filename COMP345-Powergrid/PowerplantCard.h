/**
	Represents a powerplant card.
*/
#pragma once
#include <vector>
#include <string>
#include "Resource.h"
#include "Card.h"

using std::vector;

class PowerplantCard : public Card {
public:
	PowerplantCard() {}
	PowerplantCard(int number, string resourceType, int resourceQty, int cities) : number(number), resourceType(resourceType), resourceQty(resourceQty), cities(cities) {};

	int getNumber() const { return number; }
	string getResourceType() const { return resourceType; }
	int getResourceQty() const { return resourceQty; }
	int getCities() const { return cities; }

	bool operator < (const PowerplantCard& p) const
	{
		return (number < p.number);
	}

private:
	int number; //The number of the card
	string resourceType; //The type of resources needed for this plant
	int resourceQty; //The number of resources needed
	int cities; //The number of cities this card can power up
};