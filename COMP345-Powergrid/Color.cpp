#include "Color.h"
#include <string>

std::string Color::getColor(int i) {
	switch (i) {
	case 0: return "blue";
	case 1: return "yellow";
	case 2: return "green";
	case 3: return "red";
	case 4: return "pink";
	case 5: return "black";
	}
}