
#include "RoboLeg.h"

#include <iostream>

RoboLeg::RoboLeg(int x, int y, int z) : Leglike(x, y, z) {
	species="RoboLeg";

	maxHp=100;
	maxMaxHp=100;

	strength=6;
};

void RoboLeg::print() {
	std::cout << "/";
}
