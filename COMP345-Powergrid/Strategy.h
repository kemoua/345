#pragma once
#include <vector>
#include "PowerplantCard.h"
#include "City.h"

class Strategy {
public:
	virtual int executeAuction(vector<PowerplantCard> *pcs) = 0;
	virtual int executeBuyResources(PowerplantCard *pc) = 0;
	virtual int executeBuildCities(vector<City> *cs) = 0;
};