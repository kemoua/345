/**
	Represents the money of the game.
*/
#pragma once

class Money {
public:
	Money() {}
	Money(int quantity) : quantity(quantity) {}

	void setQuantity(int q) { quantity = q; }
	int getQuantity() const { return quantity; }

private:
	int quantity;
};