/**
	Represents a summary card.
	Stores the description of the card.
*/
#pragma once
#include <string>
#include <iostream>

using std::string;

class SummaryCard {
public:
	SummaryCard() {}
	string getPlayOrder() const { return playOrder; }
	string getPaymentOrder() const { return paymentOrder; }
private:
	string playOrder = "the play order";
	string paymentOrder = "the payment order";
};