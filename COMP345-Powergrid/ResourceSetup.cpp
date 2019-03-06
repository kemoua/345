#include "ResourceSetup.h"
#include "Color.h"
#include "Resource.h"

ResourceSetup::ResourceSetup() {
	for (int i = 0; i < 6; i++) {
		houses[Color::getColor(i)] = 22;
	}
	resources["coal"] = 24;
	resources["oil"] = 24;
	resources["garbage"] = 24;
	resources["uranium"] = 12;
	money = 10000;
}