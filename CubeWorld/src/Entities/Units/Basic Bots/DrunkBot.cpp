
#include "DrunkBot.h"
#include "../../../World.h"

#include "../../Items/Basic Bot Parts/WalkerBall.h"
#include "../../Items/Basic Bot Parts/RoboLeg.h"

#include "../../../Tasks/Debug/RiskWander.h"

#include <vector>

DrunkBot::DrunkBot(int x, int y, int z) : Unit(x, y, z) {
	species="DrunkBot";
	isAlive=true;

	soulHp=50;

	addedTasks.push_back(new RiskWander());

	Item* myBody=new WalkerBall(xPos, yPos, zPos);
	World::me->addItem(myBody, this, NULL, BRAIN);

	World::me->addItem(new RoboLeg(xPos, yPos, zPos), this, myBody, ORGAN);
	World::me->addItem(new RoboLeg(xPos, yPos, zPos), this, myBody, ORGAN);
}

void DrunkBot::print() {
	std::cout << "d";
}
