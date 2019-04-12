#include <iostream>
#include <map>
#include <string>
#include <Windows.h>
#include <algorithm>
#include "Game.h"
#include "MapLoader.h"
#include "CardDriver.h"
#include "Color.h"
#include "AggressivePlayer.h"
#include "ModeratePlayer.h"
#include "EnvironmentalistPlayer.h"
#include "HumanPlayer.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::sort;

//Determine winner
void Game::triggerEnd() {
	int currentIndex = 0;
	int winnerIndex = 0;
	int maxCitiesPowered = 0;
	int maxRemainingMoney = 0;
	int maxCities = 0;
	for (auto& player : gamePlayers) {
		int alimentedCities = 0;
		//Get total number of powered cities owned
		for (auto& pc : player.getPowerplantCards()) {
			if (pc.isAlimented()) {
				alimentedCities += pc.getCities();
			}
		}
		if (player.getCities().size() < alimentedCities) {
			alimentedCities = player.getCities().size();
		}
		//Compare number of powered cities
		if (alimentedCities > maxCitiesPowered) {
			winnerIndex = currentIndex;
			maxCitiesPowered = alimentedCities;
			maxRemainingMoney = player.getMoney();
			maxCities = player.getCities().size();
		}
		if (alimentedCities == maxCitiesPowered) {
			//Compare number of remaining money
			if (player.getMoney() > maxRemainingMoney) {
				winnerIndex = currentIndex;
				maxCitiesPowered = alimentedCities;
				maxRemainingMoney = player.getMoney();
				maxCities = player.getCities().size();
			}
			if (player.getMoney() == maxRemainingMoney) {
				//Compare number of cities
				if (player.getCities().size() > maxCities) {
					winnerIndex = currentIndex;
					maxCitiesPowered = alimentedCities;
					maxRemainingMoney = player.getMoney();
					maxCities = player.getCities().size();
				}
			}
		}
		currentIndex++;
	}
	//Winner found
	Player winner = gamePlayers.at(winnerIndex);

	//TODO: Display winner. End Game properly.
}

void Game::triggerStep2() {
	gameStep = 2;
	currentStep = 2;
	NotifyPhase();
}

void Game::triggerStep3() {
	gameStep = 3;
	currentStep = 3;
	NotifyPhase();
}

void Game::start() {
	//Map loading
	vector<string> maps = { "MapUSA.txt", "MapBad1.txt", "MapBad2.txt" };
	MapLoader loader;
	int input;
	bool valid = false;
	int i = 0;
	cout << "Load map:" << endl;
	for (auto map : maps) {
		cout << i << ": " << map << endl;
		i++;
	}
	//Load and check if map file is valid
	while (!valid) {
		loader = MapLoader();
		cout << "Enter choice: ";
		cin >> input;
		if (cin.fail() || input < 0 || input > 2) {
			cout << "Please enter a valid choice." << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
		else if (loader.loadMap(maps.at(input))) {
			valid = true;
		}
		else {
			loader.~MapLoader();
		}
		cin.clear();
	}
	gameMap = Map(loader.getRegions(), loader.getCities(), loader.getConnections());
	loader.~MapLoader();

	//Resources and cards loading
	gameResources = ResourceSetup();
	gameCards = CardDriver();

	//Players
	Color colors;
	cout << "Enter number of players: ";
	cin >> input;
	while (cin.fail() || input < 2 || input > 6) {
		cout << "Please enter number between 2 and 6." << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Enter number of players: ";
		cin >> input;
	}
	cout << "selected " << input << " players" << endl;
	//For each player, assign color, elektro quantity, houses, summary card;
	SummaryCard summaryCard = SummaryCard();
	for (int i = 0; i < input; i++) {
		string currentColor = colors.getColor(i);
		Player p = Player(currentColor, 50);
		for (int j = 0; j < 22; j++) {
			p.addHouse(House(currentColor));
		}
		p.addSummaryCard(summaryCard);

		//Add strategies
		switch (i)
		{
		case 0: p.setStrategy(new HumanPlayer());
			break;
		case 1: p.setStrategy(new AggressivePlayer());
			break;
		case 2: p.setStrategy(new ModeratePlayer());
			break;
		case 3: p.setStrategy(new EnvironmentalistPlayer());
			break;
		case 4: p.setStrategy(new HumanPlayer());
			break;
		case 5: p.setStrategy(new HumanPlayer());
			break;
		default:
			break;
		}
		gamePlayers.push_back(p);
	}
	for (auto p : gamePlayers) {
		cout << p.getColor() << ", number of houses: " << p.getHouses().size();
		cout << ", elektro: " << p.getMoney() << endl;
		p.displayResources(); //display nothing since the player has no resources at the start of the game
		cout << p.getSummaryCard().getPlayOrder() << endl;
	}
	cout << endl;

	//Select Regions
	int count = 0;
	string regionChoice;
	vector<string> regionsChosen;
	int maxNumberRegions = 0;
	switch (input) {
	case 2: maxNumberRegions = 3;
		break;
	case 3: maxNumberRegions = 3;
		break;
	case 4: maxNumberRegions = 4;
		break;
	case 5: maxNumberRegions = 5;
		break;
	case 6: maxNumberRegions = 5;
	}
	cout << "You need to select " << maxNumberRegions << " regions." << endl;
	while (count < maxNumberRegions) {
		cout << "Please select a region between: ";
		if (count == 0) {
			for (auto rg : gameMap.getRegions()) {
				cout << rg.getName() << " ";
			}
		}
		else {
			//Add adjacent regions to the list of possible regions to choose
			for (auto r : gameMap.getRegionAdjacency(regionsChosen)) {
				if (!(std::find(regionsChosen.begin(), regionsChosen.end(), r) != regionsChosen.end())) {
					cout << r << " ";
				}
			}
		}
		cout << endl;
		cin >> regionChoice;
		//
		// I'm assuming the user enters correct values. You can add tests for the user input here.
		// They would be similar to the tests used above for the input of the map choice and the number of players.
		//
		regionsChosen.push_back(regionChoice);
		count++;
	}
	//Update the list of available cities depending on the regions chosen
	gameMap.setAvailableRegionsAndCities(regionsChosen);

	//Display available regions and cities for players
	cout << "Regions available: ";
	for (auto region : gameMap.getAvailableRegions()) {
		cout << region.getName() << " ";
	}
	cout << endl;
	cout << "Cities available: ";
	for (auto city : gameMap.getAvailableCities()) {
		cout << city.getName() << " ";
	}
	cout << endl;
	cout << "**************************************************" << endl;

	currentStep = 1;
}

//Determine new player order
void Game::phase1() {
	sort(gamePlayers.begin(), gamePlayers.end());
	currentPhase = 1;
	currentPlayer = &gamePlayers.at(0);
	currentAction = "";
	NotifyPhase();
	NotifyStats();
}

//Helper method
void updatePlayersNotDone(vector<Player>* playersPtr, Player p) {
	for (auto it = (*playersPtr).begin(); it != (*playersPtr).end();) {
		if (*it == p ) {
			it = (*playersPtr).erase(it);
			break;
		}
		else {
			++it;
		}
	}
}

//Helper method to handle the bidding phase
Player bidPhase(vector<Player>* playersNotDone, PowerplantCard* cardBid, vector<Player>* gamePlayersPtr, string rt) {
	vector<Player> bidPlayers = *playersNotDone; //Keep track of the original list of players who can make an action
	vector<Player>* bidPlayersPtr = &bidPlayers; //Keep track of list of players who can bid
	bool bid = true;
	int minimumBid = bidPlayers.size() == 1 ? cardBid->getNumber() : cardBid->getNumber() - 1; //Keep track of the minimum possible bid on the card
	int bidInput, strategyBid;
	while (bid) {
		//Bid is over when there's only one possible bidder
		if (bidPlayers.size() == 1) {
			cout << "****            END OF AUCTION                ****" << endl;
			cout << "Winner of the auction is " << bidPlayers.at(0).getColor();
			cout << " with a bid of " << minimumBid << " elektro." << endl;
			cout << "**************************************************" << endl;
			bid = false;
		}
		else {
			int index = 0;
			//Go through each remaining bidder in order
			while (bidPlayers.size() > 1) {
				Player player = bidPlayers.at(index);
				cout << "Player " << player.getColor() << " with " << player.getMoney() << " elektro enter bid: ";
				//Use strategy
				strategyBid = player.executeBidStrategy(cardBid, minimumBid + 1);
				if (strategyBid == 99) {
					cin >> bidInput;
				}
				else {
					bidInput = strategyBid;
				}
				while (bidInput != 0 && (bidInput < (minimumBid + 1) || bidInput > player.getMoney())) {
					cout << "You must bid at least " << (minimumBid + 1) << " elektro and you cannot bid more than what you have." << endl;
					cout << "Enter new bid: ";
					cin >> bidInput;
				}
				//If user input 0, he gets out of the auction
				if (bidInput == 0) {
					for (auto it = (*bidPlayersPtr).begin(); it != (*bidPlayersPtr).end();) {
						if ((*it) == player) {
							it = (*bidPlayersPtr).erase(it);
							break;
						}
						else {
							++it;
						}
					}
				}
				else {
					minimumBid = bidInput;
					//Check if the other players have enough money for the minimum bid
					for (auto it = (*bidPlayersPtr).begin(); it != (*bidPlayersPtr).end();) {
						if (!((*it) == player) && (*it).getMoney() < (minimumBid + 1)) {
							it = (*bidPlayersPtr).erase(it);
						}
						else {
							++it;
						}
					}
					index++;
				}
				if (index >= bidPlayers.size()) {
					index = 0;
				}
			}
		}
	}
	//Player winning the bid gets the card
	(*cardBid).setResourceType(rt);
	for (Player& player : *gamePlayersPtr) {
		if (player == bidPlayers.at(0)) {
			player.buyPowerplantCard(*cardBid, minimumBid);
			break;
		}
	}

	//Return the winner of the auction
	return (bidPlayers.at(0));
}

//Auction powerplants
void Game::phase2() {
	currentPhase = 2;
	int choice, strategyChoice;
	string resourceType;
	vector<Player> playersNotDone = gamePlayers; //Keep track of the players who can still make an action
	vector<Player>* gamePlayersPtr = &gamePlayers;
	vector<Player>* playersPtr = &playersNotDone;
	PowerplantCard* cardBid = nullptr;
	while (!playersNotDone.empty()) {
		Player player = playersNotDone.at(0);
		currentPlayer = &player;
		currentAction = "Select powerplant card for auction";
		NotifyPhase();
		choice = 0;
		//Display cards on board
		cout << "Powerplant cards on board: " << endl;
		for (auto card : gameCards.getCardsOnBoard()) {
			card.displayCard();
		}
		cout << endl;
		//Player choose action
		if (player.makeAuction(&gameCards.getCardsOnBoard())) {
			//Select powerplant card
			bool validCard = false;
			while (!validCard) {
				cout << "Enter the number of the card you want: ";
				//Get the powerplant card number with the strategy
				strategyChoice = player.executeAuctionStrategy(&gameCards.getCardsOnBoard());
				//Inputs choice if no strategies were implemented
				if (strategyChoice == 99) {
					cin >> choice;
				}
				else {
					choice = strategyChoice;
					cout << choice << endl;
				}
				for (auto card : gameCards.getCardsOnBoard()) {
					//Check if the user has enough money for the selected card
					if (card.getNumber() == choice) {
						if (card.getNumber() <= player.getMoney()) {
							resourceType = card.getResourceType();
							cardBid = &card;
							validCard = true;
							break;
						}
						else {
							cout << "You don't have enough money." << endl;
						}
					}
				}
				if (!validCard) {
					cout << "This is not a valid card." << endl;
				}
			}
			currentAction = "Bidding on powerplant card";
			NotifyPhase();
			Player winningBidder = bidPhase(playersPtr, cardBid, gamePlayersPtr, resourceType);
			//Update game after an auction is over
			updatePlayersNotDone(playersPtr, winningBidder);
			gameCards.buyCard((*cardBid).getNumber());
			NotifyStats();
		}
		else {
			updatePlayersNotDone(playersPtr, player);
		}
	}

	//Display each player possessions
	//for (auto player : gamePlayers) {
	//	cout << "Player " << player.getColor() << " has: ";
	//	for (auto powerplantCard : player.getPowerplantCards()) {
	//		cout << powerplantCard.getNumber() << " ";
	//	}
	//	cout << endl;
	//}
}

//Helper method
void displayOwnedPCards(Player player) {
	int position = 1;
	for (auto pCard : player.getPowerplantCards()) {
		cout << position << "- (has " << pCard.getAvailableResources().size() << " resources on it) ";
		pCard.displayCard();
		position++;
	}
}

//Buy resources
void Game::phase3() {
	currentPhase = 3;
	currentAction = "Buy resources for powerplants";
	for (vector<Player>::reverse_iterator player = gamePlayers.rbegin(); player != gamePlayers.rend(); ++player) {
		int strategyChoice = 99;
		int strategyCardChoice = 1; //This is used to iterate through each cards owned by a player with a strategy implemented for buying resources
		currentPlayer = &(*player);
		NotifyPhase();
		//Skip player turn if he has no powerplant cards
		if ((*player).getPowerplantCards().size() == 0) {
			cout << "Player " << (*player).getColor() << " has no powerplant cards." << endl;
			continue;
		}
		else {
			bool buyingResources = true;
			//
			//Buying resources phase
			//
			while (buyingResources) {
				cout << "****    Player " << (*player).getColor() << "    ****" << endl;
				//Display list of powerplants owned by player
				displayOwnedPCards(*player);
				int cardChoice = -1;
				//Use Strategy
				if (strategyCardChoice > (*player).getPowerplantCards().size()) { //if iterated through all cards owned by player
					strategyChoice = 0;
				}
				else {
					strategyChoice = (*player).executeBuyResourcesStrategy(&(*player).getPowerplantCards().at(strategyCardChoice - 1), &gameResources);
				}
				if (strategyChoice == 99) {
					while (cardChoice < 0 || cardChoice >(*player).getPowerplantCards().size()) {
						cout << "Enter card for which you want to buy resources: ";
						cin >> cardChoice;
					}
				}
				else {
					cardChoice = strategyChoice == 0 ? strategyChoice : strategyCardChoice;
					strategyCardChoice++;
				}
				//End buying phase for the user when he inputs 0
				if (cardChoice == 0) {
					//
					//TODO: Reallocating resources
					//
					displayOwnedPCards(*player);
					buyingResources = false;
					break;
				}
				vector<PowerplantCard> pcs = (*player).getPowerplantCards();
				PowerplantCard selectedPC = (*player).getPowerplantCards().at(cardChoice - 1);
				string resourceChoice;
				int qtyChoice;
				string confirmChoice;
				//Display number of resources on the owned powerplant
				cout << "This powerplant has " << selectedPC.getAvailableResources().size() << endl;
				//Indicates how many resources the user can buy for the plant
				if ((2 * selectedPC.getResourceQty() - selectedPC.getAvailableResources().size()) == 0) {
					cout << "You can't buy more resources for this powerplant." << endl;
					continue;
				}
				cout << "You can buy " << (2 * selectedPC.getResourceQty() - selectedPC.getAvailableResources().size()) << " " << selectedPC.getResourceType() << endl;
				cout << "What would you like to buy? (resource quantity)" << endl;
				if (strategyChoice == 99) {
					cin >> resourceChoice >> qtyChoice;
					cout << "This would cost you: " << gameResources.getPrice(resourceChoice, qtyChoice) << " elektro." << endl;
					cout << "Confirm purchase? ";
					cin >> confirmChoice;
				}
				else {
					//Strategy gives the quantity of resources to buy
					resourceChoice = selectedPC.getResourceType();
					qtyChoice = strategyChoice;
					cout << resourceChoice << " " << qtyChoice << endl;
					confirmChoice = qtyChoice == 0 ? "no" : "yes";
				}
				if (confirmChoice == "yes" || confirmChoice == "y" || confirmChoice == "1") {
					//When buying resources for the plant
					for (int i = 0; i < qtyChoice; i++) {
						Resource r = Resource(gameResources.getNextResource(resourceChoice));
						//Remove the resources from the board
						gameResources.removeResource(resourceChoice, 1);
						int index = 0;
						//Add the resources to the correct powerplant card
						for (auto& pc : pcs) {
							if (index == (cardChoice - 1)) {
								pc.addAvailableResource(r);
								break;
							}
							else {
								index++;
							}
						}
					}
					(*player).updatePowerplantCards(pcs);
					NotifyStats();
				}
			}
		}

	}
}

//Return list of cities where the player can build a house in
vector<City> getAvailableCities(Player player, Map m, int step) {
	vector<City> availableCities;
	//If the player has no city, he can build a house on any available city
	if (player.getCities().size() == 0) {
		for (City& city : m.getAvailableCities()) {
			if (city.getHouses().size() < step) {
				availableCities.push_back(city);
			}
		}
	}
	else {
		//If the player is at least in one city, the available cities are determined by the connections 
		for (auto city : player.getCities()) {
			for (City& c : m.getConnectionsForCity(city)) {
				for (City& aCity : m.getAvailableCities()) {
					if (c.getName() == aCity.getName()) {
						if (aCity.getHouses().size() < step) {
							availableCities.push_back(aCity);
						}
						break;
					}
				}
			}
		}
	}
	return availableCities;
}

//Building
void Game::phase4() {
	currentPhase = 4;
	currentAction = "Build a house in a city";
	int strategyChoice;
	for (vector<Player>::reverse_iterator player = gamePlayers.rbegin(); player != gamePlayers.rend(); ++player) {
		currentPlayer = &(*player);
		NotifyPhase();
		vector<City> availableCities = getAvailableCities(*player, gameMap, gameStep);
		if (availableCities.size() == 0) {
			cout << "You can't buy houses for now." << endl;
			continue;
		}
		cout << "****    Player " << (*player).getColor() << "    ****" << endl;
		cout << "Choose a city:" << endl;
		int index = 1;
		int cityChoice;
		//Player choose city to buy a house in
		for (auto city : availableCities) {
			cout << index << ": " << city.getName() << " (has " << city.getHouses().size() << " house(s))" << endl;
			index++;
		}
		//Use Strategy
		strategyChoice = (*player).executeBuildCitiesStrategy(&availableCities);
		if (strategyChoice == 99) {
			cin >> cityChoice; //TODO: Add validation
		}
		else {
			cityChoice = strategyChoice;
			cout << cityChoice << endl;
		}
		if (cityChoice == 0) {
			continue;
		}
		bool bought = false;
		while (!bought) {
			City chosenCity = availableCities.at(cityChoice - 1);
			int connectionCost = 0;
			int bestCost = -1;
			//Get lowest connection cost
			if ((*player).getCities().size() > 0) {
				connectionCost = -1;
				for (auto pcity : (*player).getCities()) {
					bestCost = gameMap.getConnectionCost(chosenCity, pcity);
					if (connectionCost == -1) {
						connectionCost = bestCost;
					}
					if (bestCost != -1 && bestCost < connectionCost) {
						connectionCost = bestCost;
					}
				}
			}
			//Try to buy house in city
			cout << "The lowest connection cost is: " << connectionCost << endl;
			if ((*player).buyHouse(chosenCity, connectionCost)) {
				//If successful, add a house of the player's color in the city
				vector<City> c = gameMap.getAvailableCities();
				for (auto& city : c) {
					if (chosenCity.getName() == city.getName()) {
						city.addHouse(House((*player).getColor()));
						break;
					}
				}
				gameMap.updateAvailableCities(c);
				NotifyStats();
				bought = true;
			}
			else {
				cout << "Choose another city: ";
				cin >> cityChoice;
				if (cityChoice == 0) {
					bought = true;
				}
			}
		}
	}
	//Display possession of each player
	for (auto p : gamePlayers) {
		/*cout << p.getColor() << ": " << p.getMoney() << " elektro left, cities: ";
		for (auto c : p.getCities()) {
			cout << c.getName() << " ";
		}
		cout << endl;*/

		//Trigger step 2 if one of the player has reached 7 cities
		if (p.getCities().size() >= 17) {
			triggerEnd();
			break;
		}
		if (p.getCities().size() >= 7) {
			triggerStep2();
		}
	}
}

//Return payment based on the number of powered cities
int getPayment(int numberOfCities) {
	switch (numberOfCities) {
	case 0: return 10;
	case 1: return 22;
	case 2: return 33;
	case 3: return 44;
	case 4: return 54;
	case 5: return 64;
	case 6: return 73;
	case 7: return 82;
	case 8: return 90;
	case 9: return 98;
	case 10: return 105;
	case 11: return 112;
	case 12: return 118;
	case 13: return 124;
	case 14: return 129;
	case 15: return 134;
	case 16: return 138;
	case 17: return 142;
	case 18: return 145;
	case 19: return 148;
	case 20: return 150;
	}
}

//Bureaucracy
void Game::phase5() {
	currentPhase = 5;
	currentAction = "Remove resources";
	vector<Resource> removedResources;
	for (vector<Player>::iterator player = gamePlayers.begin(); player != gamePlayers.end(); ++player) {
		currentPlayer = &(*player);
		NotifyPhase();

		//Earn money
		//First, calculate number of owned alimented cities 
		int alimentedCities = 0;
		vector<PowerplantCard> pcs = (*player).getPowerplantCards();
		//Remove the appropriate number of resources in each powered powerplant
		for (auto& pc : pcs) {
			if (pc.isAlimented() || pc.getResourceQty() == 0) {
				//If the powerplant doesn't need resources
				if (pc.getResourceQty() == 0) {
					alimentedCities += pc.getCities();
				}
				else {
					//Ask if user wants to remove the resources from a powerplant
					pc.displayCard();
					string use = "";
					cout << "Do you want to use the resources to power this plant? ";
					cin >> use;
					cout << endl;
					if (use == "1" || use == "y" || use == "yes") {
						alimentedCities += pc.getCities();
						vector<Resource> rs = pc.removeAlimentingResources();
						for (auto& r : rs) {
							removedResources.push_back(r);
						}
						(*player).updatePowerplantCards(pcs);
						NotifyStats();
					}
				}
			}
		}
		//Test if the player had less cities than what he could power up
		if ((*player).getCities().size() < alimentedCities) {
			alimentedCities = (*player).getCities().size();
		}
		int moneyEarned = getPayment(alimentedCities);
		//Pay the player
		(*player).getPayment(moneyEarned);
		cout << "Player  " << (*player).getColor() << " earned " << moneyEarned << " elektro by powering " << alimentedCities << " cities." << endl;
		NotifyStats();
	}

	//Resupply market
	gameResources.resupply(gamePlayers.size(), gameStep);

	//Discard random card and draw another one
	gameCards.removeCardRandomly();

	NotifyStats();
	//Display possession of each player
	/*for (auto p : gamePlayers) {
		cout << p.getColor() << ": " << p.getMoney() << " elektro. Powerplant Cards:" << endl;
		for (auto ppc : p.getPowerplantCards()) {
			ppc.displayCard();
			cout << "    " << ppc.getAvailableResources().size() << endl;
		}
		cout << endl;
	}*/

	//Display resources removed from powerplants and add them back to the total number of resources available
	for (auto r : removedResources) {
		cout << r.getType() << " ";
		gameResources.addResourceTotal(r.getType(), 1);
	}
	cout << endl;

	//Display resources on board
	cout << "Resources on board: " << endl;
	for (auto rb : gameResources.getResourcesOnBoard()) {
		cout << rb.first << ": " << rb.second << endl;
	}
}