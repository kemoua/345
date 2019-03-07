#pragma once
#include <string>

using std::string;

class Card {
public :
	Card() {}
	Card(string cardType) : cardType(cardType) {};

	string getCardType() const { return cardType; }

private:
	string cardType;
};