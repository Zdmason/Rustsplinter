
#include "ZombieBot.h"
#include "../../../World.h"

#include "../../Items/Basic Bot Parts/RoboLeg.h"
#include "../../Items/Basic Bot Parts/RoboBody.h"
#include "../../Items/Basic Bot Parts/RoboArm.h"
#include "../../Items/Basic Bot Parts/RoboHead.h"

#include "../../../Actions/Debug/Shamble.h"
#include "../../../Tasks/Debug/Wander.h"

#include <vector>

ZombieBot::ZombieBot(int x, int y, int z) : Unit(x, y, z) {
	species="ZombieBot";
	isAlive=true;

	addedActions.push_back(new Shamble());
	addedTasks.push_back(new Wander());

	Item* myBody=new RoboBody(xPos, yPos, zPos);
	World::me->addItem(myBody, this, NULL, ORGAN);

	World::me->addItem(new RoboHead(xPos, yPos, zPos), this, myBody, BRAIN);

	World::me->addItem(new RoboArm(xPos, yPos, zPos), this, myBody, ORGAN);

	World::me->addItem(new RoboArm(xPos, yPos, zPos), this, myBody, ORGAN);

	World::me->addItem(new RoboLeg(xPos, yPos, zPos), this, myBody, ORGAN);

	World::me->addItem(new RoboLeg(xPos, yPos, zPos), this, myBody, ORGAN);
}

void ZombieBot::print() {
	std::cout << "Z";
}
