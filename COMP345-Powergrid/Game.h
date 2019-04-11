#pragma once
#include <vector>
#include "Map.h"
#include "Player.h"
#include "ResourceSetup.h"
#include "CardDriver.h"
#include "Subject.h"

using std::vector;

class Game : public Subject {
public:
	Game() : gameStep(1) {}
	~Game() {}
	void triggerStep2(); //To implement in .cpp since it will have more actions to handle
	void triggerStep3(); //To implement in .cpp since it will have more actions to handle
	void triggerEnd();
	int getStep() const { return gameStep; }
	void start();
	void phase1();
	void phase2();
	void phase3();
	void phase4();
	void phase5();

	int getCurrentStep() const { return currentStep; }
	int getCurrentPhase() const { return currentPhase; }
	string getCurrentAction() const { return currentAction; }
	Player getCurrentPlayer() const { return *currentPlayer; }
	vector<Player> getGamePlayers() const { return gamePlayers; }


private:
	Map gameMap;
	vector<Player> gamePlayers;
	ResourceSetup gameResources;
	CardDriver gameCards;
	int gameStep;
	int currentStep;
	int currentPhase;
	string currentAction;
	Player* currentPlayer;
};