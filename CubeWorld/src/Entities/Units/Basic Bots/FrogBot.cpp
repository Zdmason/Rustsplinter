
#include "FrogBot.h"
#include "../../../World.h"

#include "../../Items/Basic Bot Parts/WalkerBall.h"
#include "../../Items/Basic Bot Parts/RoboLeg.h"

#include "../../../Actions/Debug/FrogLeap.h"
#include "../../../Tasks/Debug/SpamLeap.h"

#include <vector>

FrogBot::FrogBot(int x, int y, int z) : Unit(x, y, z) {
	species="FrogBot";
	isAlive=true;

	addedActions.push_back(new FrogLeap());
	addedTasks.push_back(new SpamLeap());

	Item* myBody=new WalkerBall(xPos, yPos, zPos);
	World::me->addItem(myBody, this, NULL, BRAIN);

	World::me->addItem(new RoboLeg(xPos, yPos, zPos), this, myBody, ORGAN);

	World::me->addItem(new RoboLeg(xPos, yPos, zPos), this, myBody, ORGAN);
}

void FrogBot::print() {
	std::cout << "f";
}
