#pragma once
#include <vector>
#include "PowerplantCard.h"
#include "Card.h"

class CardDriver {
public:
	CardDriver();
	~CardDriver() {};
	vector<PowerplantCard> getCards() const { return cards; }
	vector<PowerplantCard> getCardsOnBoard() const { return cardsOnBoard; }
	void shuffleCards();
	void drawCard();
	bool buyCard(int number);

private:
	vector<PowerplantCard> cards;
	vector<PowerplantCard> cardsOnBoard;
};