#pragma once
#include "Strategy.h"

class AggressivePlayer : public Strategy {
public:
	int executeAuction(vector<PowerplantCard> *pcs);
	int executeBuyResources(PowerplantCard *pc);
	int executeBuildCities(vector<City> *cs);
};