#include "PowerplantCard.h"

bool PowerplantCard::addAvailableResource(Resource r) {
	if (availableResources.size() < (resourceQty * 2)) {
		availableResources.push_back(r);
		if (availableResources.size() >= resourceQty) {
			alimented = true;
		}
		return true;
	}
	else {
		return false;
	}
}

int PowerplantCard::reallocateResource(string resourceName, int quantity) {
	int q = 0;
	for (auto it = availableResources.begin(); it != availableResources.end();) {
		if (q == quantity) {
			break;
		}
		if ((*it).getType() == resourceName) {
			it = availableResources.erase(it);
			q++;
		}
		else {
			++it;
		}
	}
	alimented = (availableResources.size() >= resourceQty);
	return q;
}

void PowerplantCard::displayCard() const {
	std::cout << number << ": " << resourceType << " x" << resourceQty << " for " << cities << " city/cities" << std::endl;
}