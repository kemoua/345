#pragma once
#include <string>

class City {
public:
	City() {}
	City(std::string name) : name(name) {}
	std::string getName() const { return name; }
	void setName(std::string name) { this->name = name; }
private:
	std::string name;
};