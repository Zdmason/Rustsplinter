
#include "RoboArm.h"

#include <iostream>

RoboArm::RoboArm(int x, int y, int z) : Handlike(x, y, z) {
	species="RoboArm";

	maxHp=100;
	maxMaxHp=100;

	strength=6;
};

void RoboArm::print() {
	std::cout << "|";
}
