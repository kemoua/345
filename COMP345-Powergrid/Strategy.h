#pragma once
#include <vector>
#include "PowerplantCard.h"
#include "City.h"
#include "ResourceSetup.h"

class Strategy {
public:
	virtual int executeAuction(vector<PowerplantCard> *pcs, int money) = 0;
	virtual int executeBid(PowerplantCard *pc, int minimumBid, int playerMoney) = 0;
	virtual int executeBuyResources(PowerplantCard *pc, ResourceSetup * rs, int playermoney) = 0;
	virtual int executeBuildCities(vector<City> *cs, int playerMoney) = 0;
};