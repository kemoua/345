#pragma once
#include "PhaseObserver.h"
#include "Game.h"

class GameDriver : public PhaseObserver {
public:
	GameDriver();
	~GameDriver();
	void run();
	void UpdatePhase();
	void DisplayPhase();

private:
	Game *game;
};