
#include "WalkerBot.h"
#include "../../../World.h"

#include "../../Items/Basic Bot Parts/WalkerBall.h"

#include "../../../Tasks/Debug/Wander.h"

#include <vector>

WalkerBot::WalkerBot(int x, int y, int z) : Unit(x, y, z) {
	species="WalkerBot";
	isAlive=true;

	soulHp=30;

	addedTasks.push_back(new Wander());

	World::me->addItem(new WalkerBall(xPos, yPos, zPos), this, NULL, BRAIN);
}

void WalkerBot::print() {
	std::cout << "w";
}
