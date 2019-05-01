
#include "RoboHead.h"

#include <iostream>

RoboHead::RoboHead(int x, int y, int z) : Item(x, y, z) {
	species="RoboHead";
	maxHp=100;
	maxMaxHp=100;

	selfTags.insert(CORELIKE);
}

void RoboHead::print() {
	std::cout << "o";
}
