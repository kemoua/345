/**
	Represents a house.
*/
#pragma once
#include <string>

using std::string;

class House {
public:
	House() {}
	House(string color) : color(color) {}
	string getColor() const { return color; }

private:
	string color;
};