/**
	Represents a resource.
*/
#pragma once
#include <string>

using std::string;

class Resource {
public:
	Resource() {}
	Resource(string type) : type(type) {}
	Resource(string type, int cost) : type(type), cost(cost) {}

	string getType() const { return type; }
	int getCost() const { return cost; }

private:
	string type;
	int cost;
};
