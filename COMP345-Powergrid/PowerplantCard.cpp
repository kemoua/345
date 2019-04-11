#include "PowerplantCard.h"

void PowerplantCard::addAvailableResource(Resource r) {
	if (canAddResource) {
		availableResources.push_back(r);
		if (availableResources.size() >= resourceQty) {
			alimented = true;
		}
		if (availableResources.size() == (resourceQty * 2)) {
			canAddResource = false;
		}
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
	canAddResource = !(availableResources.size() == (resourceQty * 2));
	return q;
}

void PowerplantCard::displayCard() const {
	std::cout << number << ": " << resourceType << " x" << resourceQty << " for " << cities << " city/cities" << std::endl;
}

vector<Resource> PowerplantCard::removeAlimentingResources() {
	vector<Resource> removedResources;
	if (alimented) {
		int i = 0;
		for (auto it = availableResources.begin(); it != availableResources.end();) {
			if (i < resourceQty) {
				removedResources.push_back((*it));
				it = availableResources.erase(it);
				i++;
			}
			else {
				break;
			}
		}
	}
	return removedResources;
}