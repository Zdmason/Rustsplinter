
#include "PickupBot.h"
#include "../../../World.h"

#include "../../Items/Basic Bot Parts/WalkerBall.h"
#include "../../Items/Basic Bot Parts/RoboPack.h"
#include "../../Items/Basic Bot Parts/RoboArm.h"

#include "../../../Actions/Debug/Grab.h"
#include "../../../Actions/Debug/Store.h"
#include "../../../Tasks/Debug/SpamStore.h"
#include "../../../Tasks/Debug/SpamPickup.h"
#include "../../../Tasks/Debug/RiskWander.h"

#include <vector>

PickupBot::PickupBot(int x, int y, int z) : Unit(x, y, z) {
	species="PickupBot";
	isAlive=true;

	soulHp=60;

	addedTasks.push_back(new SpamStore());
	addedTasks.push_back(new SpamPickup());
	addedTasks.push_back(new RiskWander());

	Item* myBody=new WalkerBall(xPos, yPos, zPos);
	World::me->addItem(myBody, this, NULL, BRAIN);

	Item* myArm=new RoboArm(xPos, yPos, zPos);
	World::me->addItem(myArm, this, myBody, ORGAN);

	World::me->addItem(new RoboPack(xPos, yPos, zPos), this, myBody, ORGAN);
}

void PickupBot::print() {
	std::cout << "p";
}
