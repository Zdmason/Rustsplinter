
#include "RoboRock.h"

#include <iostream>

RoboRock::RoboRock(int x, int y, int z) : Item(x, y, z) {
	species="RoboRock";

	maxHp=50;
	maxMaxHp=50;
};

void RoboRock::print() {
	std::cout << ".";
}
