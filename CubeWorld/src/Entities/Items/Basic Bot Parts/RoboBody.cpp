
#include "RoboBody.h"

#include <iostream>

RoboBody::RoboBody(int x, int y, int z) : Item(x, y, z) {
	species="RoboBody";

	maxHp=150;
	maxMaxHp=150;

	selfTags.insert(CORELIKE);
}

void RoboBody::print() {
	std::cout << "O";
}
