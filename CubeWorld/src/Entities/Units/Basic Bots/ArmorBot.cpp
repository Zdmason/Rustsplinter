
#include "ArmorBot.h"
#include "../../../World.h"

#include "../../Items/Basic Bot Parts/RoboLeg.h"
#include "../../Items/Basic Bot Parts/RoboBody.h"
#include "../../Items/Basic Bot Parts/RoboArm.h"
#include "../../Items/Basic Bot Parts/RoboHead.h"
#include "../../Items/Basic Bot Parts/IronPlate.h"

#include "../../../Tasks/Debug/RiskWander.h"

#include <vector>

ArmorBot::ArmorBot(int x, int y, int z) : Unit(x, y, z) {
	species="ArmorBot";
	isAlive=true;

	soulHp=50;

	addedTasks.push_back(new RiskWander());

	Item* newPart=World::me->addItem(new RoboHead(xPos, yPos, zPos), this, NULL, BRAIN);
	World::me->addItem(new IronPlate(xPos, yPos, zPos), this, newPart, ARMORING);

	Item* myBody=World::me->addItem(new RoboBody(xPos, yPos, zPos), this, newPart, ORGAN);
	World::me->addItem(new IronPlate(xPos, yPos, zPos), this, myBody, ARMORING);

	newPart=World::me->addItem(new RoboArm(xPos, yPos, zPos), this, myBody, ORGAN);
	World::me->addItem(new IronPlate(xPos, yPos, zPos), this, newPart, ARMORING);

	newPart=World::me->addItem(new RoboArm(xPos, yPos, zPos), this, myBody, ORGAN);
	World::me->addItem(new IronPlate(xPos, yPos, zPos), this, newPart, ARMORING);

	newPart=World::me->addItem(new RoboLeg(xPos, yPos, zPos), this, myBody, ORGAN);
	World::me->addItem(new IronPlate(xPos, yPos, zPos), this, newPart, ARMORING);

	newPart=World::me->addItem(new RoboLeg(xPos, yPos, zPos), this, myBody, ORGAN);
	World::me->addItem(new IronPlate(xPos, yPos, zPos), this, newPart, ARMORING);
}

void ArmorBot::print() {
	std::cout << "A";
}
