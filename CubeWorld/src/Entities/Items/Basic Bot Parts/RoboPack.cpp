
#include "RoboPack.h"

#include <iostream>

RoboPack::RoboPack(int x, int y, int z) : Item(x, y, z) {
	species="RoboPack";

	maxHp=50;
	maxMaxHp=50;
};

void RoboPack::print() {
	std::cout << "p";
}
