#pragma once
#include "Observer.h"
#include "Game.h"

class GameDriver : public Observer {
public:
	GameDriver();
	~GameDriver();
	void run();
	void UpdatePhase();
	void DisplayPhase();
	void UpdateStats();
	void DisplayStats();

private:
	Game *game;
};