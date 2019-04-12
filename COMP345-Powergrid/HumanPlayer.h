#pragma once
#include "Strategy.h"

//The human player has no strategy implemented.
//Every method return 99 which will be handled in the Game.cpp to prompt player for action.
class HumanPlayer : public Strategy {
public:
	int executeAuction(vector<PowerplantCard> *pcs, int money) { return 99; }
	int executeBid(PowerplantCard *pc, int minimumBid, int playerMoney) { return 99; }
	int executeBuyResources(PowerplantCard *pc, ResourceSetup * rs, int playermoney) { return 99; }
	int executeBuildCities(vector<City> *cs, int playerMoney) { return 99; }
};