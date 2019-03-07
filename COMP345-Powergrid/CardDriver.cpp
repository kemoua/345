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
	//Try to load the powerplant cards from a txt file
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
			//The handling of a card depends on its value
			if (number == 0) { //Represents the step 3 card
				step = PowerplantCard(number, resourceType, resourceQty, cities);
				continue;
			}
			if (number == 13) { //This is the card that will be put on the top of the deck
				pc13 = PowerplantCard(number, resourceType, resourceQty, cities);
				continue;
			}
			if (number >= 3 && number <= 10) { //Those are the cards that will be put on the board at the beginning
				cardsOnBoard.push_back(PowerplantCard(number, resourceType, resourceQty, cities));
				continue;
			}
			temp.push_back(PowerplantCard(number, resourceType, resourceQty, cities));
		}
		input.close();

		//Shuffle the cards
		std::srand(time(0));
		std::random_shuffle(std::begin(temp), std::end(temp));
		cards.push_back(step); //Put the step card at the start of the vector
		for (auto c : temp) {
			cards.push_back(c); //Push the shuffled cards in the vector
		}
		cards.push_back(pc13); //Put the card number 13 at the end of the vector
	}
}

void CardDriver::shuffleCards() {
	std::srand(time(0));
	std::random_shuffle(std::begin(cards), std::end(cards));
}

void CardDriver::drawCard() {
	if (cards.size() == 0) { //Test if there are cards left in the deck
		cout << "No more cards to draw" << endl;
	}
	else {
		PowerplantCard nextCard = cards.back(); //Draw cards from the end of the vector
		cardsOnBoard.push_back(nextCard);
		std::sort(std::begin(cardsOnBoard), std::end(cardsOnBoard)); //Sort the cards on the board
		cards.pop_back();
	}
}

bool CardDriver::buyCard(int number) {
	vector<PowerplantCard>::iterator it;
	for (it = cardsOnBoard.begin(); it != cardsOnBoard.end(); ++it) {
		if (it->getNumber() == number) {
			cardsOnBoard.erase(it); //Remove the card that was bought from the board
			drawCard();	//Draw a card to replace the one removed
			return true;
		}
	}
	return false;
}

//Simple display of the content of the summary card
void CardDriver::viewSummary() const {
	cout << summary.getPaymentOrder() << endl;
	cout << summary.getPlayOrder() << endl;
}