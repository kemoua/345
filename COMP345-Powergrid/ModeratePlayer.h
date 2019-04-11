#pragma once
#include "Strategy.h"

class ModeratePlayer : public Strategy {
public:
	int executeAuction(vector<PowerplantCard> *pcs, int money);
	int executeBid(PowerplantCard *pc, int minimumBid, int playerMoney);
	int executeBuyResources(PowerplantCard *pc, ResourceSetup * rs, int playermoney);
	int executeBuildCities(vector<City> *cs, int playerMoney);
};