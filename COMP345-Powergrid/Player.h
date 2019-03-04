#pragma once
#include <string>

using std::string;

class Player {
public:
	Player();
	Player(string color, int elektro, int resource);
	~Player();

	string getColor() const { return color; }
	void setColor(string color) { this->color = color; }

	int getElektro() const { return elektro; }
	void setElektro(int elektro) { this->elektro = elektro; }

	int getResource() const { return resource; }
	void setResource(int resource) { this->resource = resource; }

private:
	string color;
	int elektro;
	int resource;
	int city;
};