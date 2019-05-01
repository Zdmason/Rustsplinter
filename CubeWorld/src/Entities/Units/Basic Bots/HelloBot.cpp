
#include "HelloBot.h"
#include "../../../World.h"

#include "../../Items/Basic Bot Parts/WalkerBall.h"

#include <vector>

HelloBot::HelloBot(int x, int y, int z) : Unit(x, y, z) {
	species="HelloBot";
	isAlive=true;

	World::me->addItem(new WalkerBall(xPos, yPos, zPos), this, NULL, BRAIN);
}

void HelloBot::print() {
	std::cout << "h";
}
