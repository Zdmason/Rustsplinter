
#include "BlobbingBot.h"
#include "../../../World.h"

#include "../../Items/Basic Bot Parts/WalkerBall.h"
#include "../../Items/Basic Bot Parts/RoboArm.h"

#include "../../../Actions/Debug/DebugKarate.h"
#include "../../../Tasks/Debug/SpamKarate.h"

#include <vector>

BlobbingBot::BlobbingBot(int x, int y, int z) : Unit(x, y, z) {
	species="BlobbingBot";
	isAlive=true;

	addedActions.push_back(new DebugKarate());
	addedTasks.push_back(new SpamKarate());

	Item* myBody=new WalkerBall(xPos, yPos, zPos);
	World::me->addItem(myBody, this, NULL, BRAIN);

	World::me->addItem(new RoboArm(xPos, yPos, zPos), this, myBody, ORGAN);
}

void BlobbingBot::print() {
	std::cout << "B";
}
