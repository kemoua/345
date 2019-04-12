#include "GameDriver.h"
#include <iostream>
#include "Game.h"

using std::cout;
using std::endl;

GameDriver::GameDriver() {
	Game::instance();
	Game::instance()->Attach(this);
}

GameDriver::~GameDriver() {
	Game::instance()->Detach(this);
	//delete game;
	Game::instance()->ResetInstance();
}

void GameDriver::run() {
	Game::instance()->start();
	while (true) {
		Game::instance()->phase1();
		Game::instance()->phase2();
		Game::instance()->phase3();
		Game::instance()->phase4();
		Game::instance()->phase5();
	}
	//delete game;
}

void GameDriver::UpdatePhase() {
	DisplayPhase();
}

//Display phase info on notify
void GameDriver::DisplayPhase() {
	cout << "								**************************************************" << endl;
	cout << "								Step: " << Game::instance()->getCurrentStep() << "    Phase " << Game::instance()->getCurrentPhase() << endl;
	cout << "								Player order: ";
	if (Game::instance()->getCurrentPhase() == 3 || Game::instance()->getCurrentPhase() == 4) {
		vector<Player> p = Game::instance()->getGamePlayers();
		for (vector<Player>::reverse_iterator it = p.rbegin(); it != p.rend(); ++it) {
			cout << (*it).getColor() << " ";
		}
	}
	else {
		for (auto player : Game::instance()->getGamePlayers()) {
			cout << player.getColor() << " ";
		}
	}
	cout << endl << "								Player's turn: " << Game::instance()->getCurrentPlayer().getColor() << endl;
	cout << "								Current Action: " << Game::instance()->getCurrentAction() << endl;
	cout << "								**************************************************" << endl;
}

void GameDriver::UpdateStats() {
	DisplayStats();
}

//Display stats on notify
void GameDriver::DisplayStats() {
	cout << "						**************************************************" << endl;
	//For each players
	for (auto player : Game::instance()->getGamePlayers()) {
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