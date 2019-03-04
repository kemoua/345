#pragma once
#include <string>

using std::string;

class Region {
public:
	Region() {}
	Region(string name) : name(name) {}
	string getName() const { return name; }
	void setName(string name) { this->name = name; }
private:
	string name;
};