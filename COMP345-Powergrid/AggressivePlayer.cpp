#include "AggressivePlayer.h"

int AggressivePlayer::executeAuction(vector<PowerplantCard> *pcs, int money) {
	for (auto pc : *pcs) {

		//Basic strategy: pass if you need 2 resources to power a city, auction otherwise
		//It will return the number of the first card that fits the criteria.
		if (pc.getCities() != 0 && (pc.getResourceQty() / pc.getCities() < 2)) {
			if (pc.getNumber() <= money) {
				return pc.getNumber();
			}
		}
	}
	//If no cards on board fits the criteria
	return 0;
}

int AggressivePlayer::executeBid(PowerplantCard *pc, int minimumBid, int playerMoney) {
	//Always bid if the card fits the player criteria and if the player has enough money for the minimum bid
	if ((*pc).getResourceQty() / (*pc).getCities() < 2 && minimumBid <= playerMoney) {
		return minimumBid;
	}
	return 0;
}

int AggressivePlayer::executeBuyResources(PowerplantCard *pc, ResourceSetup * rs, int playermoney) {
	//No specific strategy for resources
	return 99;
}

int AggressivePlayer::executeBuildCities(vector<City> *cs, int playerMoney) {
	//No specific strategy for cities
	return 99;
}