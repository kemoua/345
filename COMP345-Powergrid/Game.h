#pragma once
#include <vector>
#include "Map.h"
#include "Player.h"
#include "ResourceSetup.h"
#include "CardDriver.h"

using std::vector;

class Game {
public:
	Game() : gameStep(1) {}
	~Game() {}
	void start();
	void phase1();
	void phase2();
	void phase3();
	void phase4();
	void phase5();

private:
	Map gameMap;
	vector<Player> gamePlayers;
	ResourceSetup gameResources;
	CardDriver gameCards;
	int gameStep;
};