
#include "KidnapperBot.h"
#include "../../../World.h"

#include "../../Items/Basic Bot Parts/WalkerBall.h"
#include "../../Items/Basic Bot Parts/RoboArm.h"

#include "../../../Actions/Debug/Grab.h"
#include "../../../Tasks/Debug/GrabAnyUnit.h"
#include "../../../Tasks/Debug/RiskWander.h"

#include <vector>

KidnapperBot::KidnapperBot(int x, int y, int z) : Unit(x, y, z) {
	species="KidnapperBot";
	isAlive=true;

	soulHp=60;

	addedTasks.push_back(new GrabAnyUnit());
	addedTasks.push_back(new RiskWander());

	Item* myBody=new WalkerBall(xPos, yPos, zPos);
	World::me->addItem(myBody, this, NULL, BRAIN);

	Item* myArm=new RoboArm(xPos, yPos, zPos);
	World::me->addItem(myArm, this, myBody, ORGAN);
}

void KidnapperBot::print() {
	std::cout << "k";
}
