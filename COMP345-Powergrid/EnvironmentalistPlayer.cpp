#include "EnvironmentalistPlayer.h"

int EnvironmentalistPlayer::executeAuction(vector<PowerplantCard> *pcs, int money) {
	int cardNumber = 0;
	for (auto pc : *pcs) {
		//Basic strategy: return the first wind plant on board.
		if (pc.getResourceQty() == 0 && pc.getCities() > 0) {
			return pc.getNumber();
		}
		//Let's say we consider a powerplant using garbage as a good powerplant for the environmentalist player.
		//It will return the first card using garbage if there's no wind plant.
		if (pc.getResourceType() == "garbage" && cardNumber == 0) {
			cardNumber = pc.getNumber();
		}
	}
	//If no cards fit the criterias, it will return 0 (equivalent to pass)
	return cardNumber;
}

int EnvironmentalistPlayer::executeBid(PowerplantCard *pc, int minimumBid, int playerMoney) {
	//Check if the card fits the player criteria
	if ((*pc).getResourceQty() == 0 || (*pc).getResourceType() == "garbage") {
		//This player preferes to buy at the end of a round.
		//I've implemented it as if the player only wants to buy a card for its minimum cost.
		if (minimumBid == (*pc).getNumber()) {
			return minimumBid;
		}
	}
	return 0;
}

int EnvironmentalistPlayer::executeBuyResources(PowerplantCard *pc, ResourceSetup * rs, int playermoney) {
	//No specific strategy for resources
	return 99;
}

int EnvironmentalistPlayer::executeBuildCities(vector<City> *cs, int playerMoney) {
	//No specific strategy for cities
	return 99;
}