
#include "SlasherBot.h"
#include "../../../World.h"

#include "../../Items/Basic Bot Parts/WalkerBall.h"
#include "../../Items/Basic Bot Parts/RoboArm.h"
#include "../../Items/Basic Bot Parts/PsychoSword.h"

#include "../../../Tasks/Debug/SpamMelee.h"

#include <vector>

SlasherBot::SlasherBot(int x, int y, int z) : Unit(x, y, z) {
	species="SlasherBot";
	isAlive=true;

	addedTasks.push_back(new SpamMelee());

	Item* myArm=new RoboArm(xPos, yPos, zPos);
	World::me->addItem(myArm, this, NULL, ORGAN);

	World::me->addItem(new WalkerBall(xPos, yPos, zPos), this, myArm, BRAIN);

	World::me->addItem(new PsychoSword(xPos, yPos, zPos), this, myArm, HELD);
}

void SlasherBot::print() {
	std::cout << "S";
}
