
#include "ThrowBot.h"
#include "../../../World.h"

#include "../../Items/Basic Bot Parts/WalkerBall.h"
#include "../../Items/Basic Bot Parts/RoboPack.h"
#include "../../Items/Basic Bot Parts/RoboArm.h"
#include "../../Items/Basic Bot Parts/RoboRock.h"
#include "../../Items/Basic Bot Parts/PsychoSword.h"

#include "../../../Tasks/Debug/SpamThrow.h"
#include "../../../Tasks/Debug/SpamPickup.h"
#include "../../../Tasks/Debug/SpamStore.h"
#include "../../../Tasks/Debug/SpamButcher.h"
#include "../../../Tasks/Debug/RiskWander.h"

#include <vector>

ThrowBot::ThrowBot(int x, int y, int z) : Unit(x, y, z) {
	species="ThrowBot";
	isAlive=true;

	soulHp=60;

	addedTasks.push_back(new SpamThrow());
	addedTasks.push_back(new SpamPickup());
	addedTasks.push_back(new SpamStore());
	addedTasks.push_back(new RiskWander());
	addedTasks.push_back(new SpamButcher());

	Item* myBody=World::me->addItem(new WalkerBall(xPos, yPos, zPos), this, NULL, BRAIN);

	World::me->addItem(new RoboArm(xPos, yPos, zPos), this, myBody, ORGAN);

	Item* myPack=World::me->addItem(new RoboPack(xPos, yPos, zPos), this, myBody, ORGAN);

	World::me->addItem(new PsychoSword(xPos, yPos, zPos), this, myPack, STORED);
	World::me->addItem(new PsychoSword(xPos, yPos, zPos), this, myPack, STORED);
	World::me->addItem(new PsychoSword(xPos, yPos, zPos), this, myPack, STORED);
//	World::me->addItem(new RoboRock(xPos, yPos, zPos), this, myPack, STORED);
//	World::me->addItem(new RoboRock(xPos, yPos, zPos), this, myPack, STORED);
//	World::me->addItem(new RoboRock(xPos, yPos, zPos), this, myPack, STORED);
//	World::me->addItem(new RoboRock(xPos, yPos, zPos), this, myPack, STORED);
//	World::me->addItem(new RoboRock(xPos, yPos, zPos), this, myPack, STORED);
//	World::me->addItem(new RoboRock(xPos, yPos, zPos), this, myPack, STORED);
//	World::me->addItem(new RoboRock(xPos, yPos, zPos), this, myPack, STORED);
//	World::me->addItem(new RoboRock(xPos, yPos, zPos), this, myPack, STORED);
//	World::me->addItem(new RoboRock(xPos, yPos, zPos), this, myPack, STORED);
//	World::me->addItem(new RoboRock(xPos, yPos, zPos), this, myPack, STORED);
}

void ThrowBot::print() {
	std::cout << "t";
}
