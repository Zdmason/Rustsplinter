
#include "SkeletonBot.h"
#include "../../../World.h"

#include "../../Items/Basic Bot Parts/RoboLeg.h"
#include "../../Items/Basic Bot Parts/RoboBody.h"
#include "../../Items/Basic Bot Parts/RoboArm.h"
#include "../../Items/Basic Bot Parts/RoboHead.h"

#include "../../../Tasks/Debug/RiskWander.h"

#include <vector>

SkeletonBot::SkeletonBot(int x, int y, int z) : Unit(x, y, z) {
	species="SkeletonBot";
	isAlive=true;

	soulHp=50;

	addedTasks.push_back(new RiskWander());

	Item* myBrain=new RoboHead(xPos, yPos, zPos);
	World::me->addItem(myBrain, this, NULL, BRAIN);

	Item* myBody=new RoboBody(xPos, yPos, zPos);
	World::me->addItem(myBody, this, myBrain, ORGAN);

	World::me->addItem(new RoboArm(xPos, yPos, zPos), this, myBody, ORGAN);

	World::me->addItem(new RoboArm(xPos, yPos, zPos), this, myBody, ORGAN);

	World::me->addItem(new RoboLeg(xPos, yPos, zPos), this, myBody, ORGAN);

	World::me->addItem(new RoboLeg(xPos, yPos, zPos), this, myBody, ORGAN);
}

void SkeletonBot::print() {
	std::cout << "s";
}
