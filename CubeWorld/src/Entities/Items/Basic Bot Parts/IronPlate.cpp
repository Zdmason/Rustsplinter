
#include "IronPlate.h"

#include <iostream>

IronPlate::IronPlate(int x, int y, int z) : Item(x, y, z) {
	species="IronPlate";

	maxHp=300;
	maxMaxHp=300;
};

void IronPlate::print() {
	std::cout << "=";
}
