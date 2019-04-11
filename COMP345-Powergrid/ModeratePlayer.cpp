#include "ModeratePlayer.h"

int ModeratePlayer::executeAuction(vector<PowerplantCard> *pcs, int money) {
	for (auto pc : *pcs) {
		//Basic strategy: This player will try to go for an efficient powerplant, as long as he has at least 35 elektros left at the end of the auction.
		//An efficient powerplant in this case is a powerplant that requires less than 2 resources for a city.
		if (pc.getCities() != 0 && (pc.getResourceQty() / pc.getCities() < 2)) {
			if (money - pc.getNumber() >= 35) {
				return pc.getNumber();
			}
		}
	}
	return 0;
}

int ModeratePlayer::executeBid(PowerplantCard *pc, int minimumBid, int playerMoney) {
	//This player will bid as long as the powerplant is efficient and he has enough elektros left to buy a city (amount set at 35 elektros)
	if ((*pc).getResourceQty() / (*pc).getCities() < 2 && playerMoney - minimumBid >= 35) {
		return minimumBid;
	}
	return 0;
}

int ModeratePlayer::executeBuyResources(PowerplantCard *pc, ResourceSetup * rs, int playerMoney) {
	//This player will buy the minimum amount of resources required by the powerplant card,
	//as long as it leaves him with enough elektros to buy a city.
	if (playerMoney - (*rs).getPrice((*pc).getResourceType(), (*pc).getResourceQty()) >= 35) {
		return (*pc).getResourceQty();
	}
	return 0;
}

int ModeratePlayer::executeBuildCities(vector<City> *cs, int playerMoney) {
	//This player will always buy the first city available
	if (!(*cs).empty()) {
		return 1;
	}
	return 0;
}