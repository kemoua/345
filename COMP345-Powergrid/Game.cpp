#include <iostream>
#include <map>
#include <string>
#include <Windows.h>
#include <algorithm>
#include "Game.h"
#include "MapLoader.h"
#include "CardDriver.h"
#include "Color.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::sort;

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
}

//Determine new player order
void Game::phase1() {
	cout << "**************************************************" << endl;
	cout << "****                PHASE 1                   ****" << endl;
	cout << "**************************************************" << endl;
	sort(gamePlayers.begin(), gamePlayers.end());
	cout << "The player order is: " << endl;
	for (auto player : gamePlayers) {
		cout << player.getColor() << " ";
	}
	cout << endl;
	cout << "**************************************************" << endl;
}

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

Player bidPhase(vector<Player>* playersNotDone, PowerplantCard* cardBid, vector<Player>* gamePlayersPtr, string rt) {
	vector<Player> bidPlayers = *playersNotDone;
	vector<Player>* bidPlayersPtr = &bidPlayers;
	bool bid = true;
	int minimumBid = bidPlayers.size() == 1 ? cardBid->getNumber() : cardBid->getNumber() - 1;
	int bidInput;
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
			while (bidPlayers.size() > 1) {
				Player player = bidPlayers.at(index);
				cout << "Player " << player.getColor() << " with " << player.getMoney() << " elektro enter bid: ";
				cin >> bidInput;
				while (bidInput != 0 && (bidInput < (minimumBid + 1) || bidInput > player.getMoney())) {
					cout << "You must bid at least " << (minimumBid + 1) << " elektro and you cannot bid more than what you have." << endl;
					cout << "Enter new bid: ";
					cin >> bidInput;
				}
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

	return (bidPlayers.at(0));
}

//Auction powerplants
void Game::phase2() {
	cout << "**************************************************" << endl;
	cout << "****                PHASE 2                   ****" << endl;
	cout << "**************************************************" << endl;
	int choice;
	string resourceType;
	vector<Player> playersNotDone = gamePlayers;
	vector<Player>* gamePlayersPtr = &gamePlayers;
	vector<Player>* playersPtr = &playersNotDone;
	PowerplantCard* cardBid = nullptr;
	while (!playersNotDone.empty()) {
		Player player = playersNotDone.at(0);
		choice = 0;
		cout << "Powerplant cards on board: " << endl;
		for (auto card : gameCards.getCardsOnBoard()) {
			card.displayCard();
		}
		cout << endl;
		while (choice != 1 and choice != 2) {
			cout << "Player " << player.getColor() << " with " << player.getMoney() << " elektro choose action:" << endl;
			cout << "1: Pass" << endl;
			cout << "2: Auction" << endl;
			cin >> choice;
		}
		if (choice == 2) {
			//Select powerplant card
			bool validCard = false;
			while (!validCard) {
				cout << "Enter the number of the card you want: ";
				cin >> choice;
				for (auto card : gameCards.getCardsOnBoard()) {
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
			Player winningBidder = bidPhase(playersPtr, cardBid, gamePlayersPtr, resourceType);
			updatePlayersNotDone(playersPtr, winningBidder);
			gameCards.buyCard((*cardBid).getNumber());
		}
		else {
			updatePlayersNotDone(playersPtr, player);
		}
	}
	for (auto player : gamePlayers) {
		cout << "Player " << player.getColor() << " has: ";
		for (auto powerplantCard : player.getPowerplantCards()) {
			cout << powerplantCard.getNumber() << " ";
		}
		cout << endl;
	}
}

//Buy resources
void Game::phase3() {
	cout << "**************************************************" << endl;
	cout << "****                PHASE 3                   ****" << endl;
	cout << "**************************************************" << endl;
	//Display the play order
	cout << "Player order: ";
	for (vector<Player>::reverse_iterator it = gamePlayers.rbegin(); it != gamePlayers.rend(); ++it) {
		cout << (*it).getColor() << " ";
	}
	cout << endl;

	for (vector<Player>::reverse_iterator player = gamePlayers.rbegin(); player != gamePlayers.rend(); ++player) {
		if ((*player).getPowerplantCards().size() == 0) {
			cout << "Player " << (*player).getColor() << " has no powerplant cards." << endl;
			continue;
		}
		else {
			bool buyingResources = true;
			while (buyingResources) {
				int position = 1;
				for (auto pCard : (*player).getPowerplantCards()) {
					cout << position << "- ";
					pCard.displayCard();
					position++;
				}
				int cardChoice = -1;
				while (cardChoice < 0 || cardChoice >(*player).getPowerplantCards().size()) {
					cout << "Enter card for which you want to buy resources: ";
					cin >> cardChoice;
				}
				if (cardChoice == 0) {
					buyingResources = false;
					break;
				}
				(*player).getPowerplantCards().at(cardChoice - 1).displayCard();
			}
		}

	}
}

