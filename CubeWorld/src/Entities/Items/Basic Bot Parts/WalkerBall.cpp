
#include "WalkerBall.h"
#include "../../../Actions/Debug/Roll.h"

#include <iostream>

WalkerBall::WalkerBall(int x, int y, int z) : Item(x, y, z) {
	species="WalkerBall";
	maxHp=300;
	maxMaxHp=300;

	selfTags.insert(CORELIKE);

	selfActions.push_back(new Roll());
};

void WalkerBall::print() {
	std::cout << "o";
}
