#pragma once
#include <string>
#include <iostream>

using std::string;

class SummaryCard {
public:
	SummaryCard() {}
	void displayPlayOrder() { std::cout << playOrder << std::endl; }
	void displayPaymentOrder() { std::cout << paymentOrder << std::endl; }
private:
	string playOrder = "the play order";
	string paymentOrder = "the payment order";
};