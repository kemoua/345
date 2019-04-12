#include "GameDriver.h"
#include <iostream>

using std::cout;
using std::endl;

GameDriver::GameDriver() {
	game = new Game();
	game->Attach(this);
}

GameDriver::~GameDriver() {
	game->Detach(this);
	delete game;
}

void GameDriver::run() {
	game->start();
	while (true) {
		game->phase1();
		game->phase2();
		game->phase3();
		game->phase4();
		game->phase5();
	}
	delete game;
}

void GameDriver::UpdatePhase() {
	DisplayPhase();
}

//Display phase info on notify
void GameDriver::DisplayPhase() {
	cout << "								**************************************************" << endl;
	cout << "								Step: " << game->getCurrentStep() << "    Phase " << game->getCurrentPhase() << endl;
	cout << "								Player order: ";
	if (game->getCurrentPhase() == 3 || game->getCurrentPhase() == 4) {
		vector<Player> p = game->getGamePlayers();
		for (vector<Player>::reverse_iterator it = p.rbegin(); it != p.rend(); ++it) {
			cout << (*it).getColor() << " ";
		}
	}
	else {
		for (auto player : game->getGamePlayers()) {
			cout << player.getColor() << " ";
		}
	}
	cout << endl << "								Player's turn: " << game->getCurrentPlayer().getColor() << endl;
	cout << "								Current Action: " << game->getCurrentAction() << endl;
	cout << "								**************************************************" << endl;
}

void GameDriver::UpdateStats() {
	DisplayStats();
}

//Display stats on notify
void GameDriver::DisplayStats() {
	cout << "						**************************************************" << endl;
	//For each players
	for (auto player : game->getGamePlayers()) {
		cout << "						Player " << player.getColor() << endl;

		//Display cities
		cout << "							Cities:" << endl << "							";
		for (auto city : player.getCities()) {
			cout << city.getName() << " ";
		}
		cout << endl;

		//Display powerplant cards with their resources
		cout << "							Powerplant cards:" << endl;
		for (auto card : player.getPowerplantCards()) {
			cout << "							";
			card.displayCard();
			cout << "								";
			for (auto res : card.getAvailableResources()) {
				cout << res.getType() << " ";
			}
			cout << endl;
		}
		cout << endl;
		//Display Money
		cout << "							Elektro: " << player.getMoney() << endl;
	}
	cout << "						**************************************************" << endl;
}