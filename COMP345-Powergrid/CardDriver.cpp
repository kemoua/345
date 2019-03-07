#include <fstream>
#include <iostream>
#include "PowerplantCard.h"
#include "SummaryCard.h"
#include "Step3.h"
#include "CardDriver.h"
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;
CardDriver::CardDriver() {
	ifstream input("PowerplantCards.txt");

	if (input.fail())
	{
		cout << "File for powerplant cards was not found" << endl;
		cout << "Exit program" << endl;
	}
	else {
		int number, resourceQty, cities;
		string resourceType;
		vector<PowerplantCard> temp;
		PowerplantCard step, pc13;

		while (!input.eof())
		{
			input >> number >> resourceType >> resourceQty >> cities;
			if (number == 0) {
				step = PowerplantCard(number, resourceType, resourceQty, cities);
				continue;
			}
			if (number == 13) {
				pc13 = PowerplantCard(number, resourceType, resourceQty, cities);
				continue;
			}
			if (number >= 3 && number <= 10) {
				cardsOnBoard.push_back(PowerplantCard(number, resourceType, resourceQty, cities));
				continue;
			}
			temp.push_back(PowerplantCard(number, resourceType, resourceQty, cities));
		}
		input.close();
		std::srand(time(0));
		std::random_shuffle(std::begin(temp), std::end(temp));

		cards.push_back(step);
		for (auto c : temp) {
			cards.push_back(c);
		}
		cards.push_back(pc13);
	}
}

void CardDriver::shuffleCards() {
	std::srand(time(0));
	std::random_shuffle(std::begin(cards), std::end(cards));
}

void CardDriver::drawCard() {
	if (cards.size() == 0) {
		cout << "No more cards to draw" << endl;
	}
	else {
		PowerplantCard nextCard = cards.back();
		cardsOnBoard.push_back(nextCard);
		std::sort(std::begin(cardsOnBoard), std::end(cardsOnBoard));
		cards.pop_back();
	}
}

bool CardDriver::buyCard(int number) {
	vector<PowerplantCard>::iterator it;
	for (it = cardsOnBoard.begin(); it != cardsOnBoard.end(); ++it) {
		if (it->getNumber() == number) {
			cardsOnBoard.erase(it);
			drawCard();
			return true;
		}
	}
	return false;
}

void CardDriver::viewSummary() const {
	cout << summary.getPaymentOrder() << endl;
	cout << summary.getPlayOrder() << endl;
}