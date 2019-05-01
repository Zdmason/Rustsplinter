
#include "RoboBullet.h"

#include <iostream>

RoboBullet::RoboBullet(int x, int y, int z) : Bulletlike(x, y, z) {
	species="RoboBullet";

	maxHp=5;
	maxMaxHp=5;
}

void RoboBullet::print() {
	std::cout << "`";
}
