
#include "RoboGun.h"

#include <iostream>

RoboGun::RoboGun(int x, int y, int z) : Gunlike(x, y, z) {
	species="RoboGun";

	maxHp=15;
	maxMaxHp=15;

	shootDamage=100;
}

void RoboGun::print() {
	std::cout << "7";
}
