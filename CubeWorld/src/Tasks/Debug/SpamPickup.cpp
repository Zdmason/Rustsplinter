
#include "SpamPickup.h"

#include "..\..\World.h"

SpamPickup::SpamPickup() : Task() {
	taskName="SpamPickup";
	priority=1;
}


bool SpamPickup::attempt(Unit* taskMaster) {

	Item* pickable=World::me->cube[taskMaster->xPos][taskMaster->yPos][taskMaster->zPos]->items.front();
	if(World::me->cube[taskMaster->xPos][taskMaster->yPos][taskMaster->zPos]->items.empty())
	{
		std::cout << "{Nothing below me to pick up} ";
		return false;
	}

	Actool* picker=taskMaster->getActool("", GRAB, NULL_ACTION_SUBTAG, NULL, pickable, NULL);
	if(picker==NULL)
	{
		std::cout << "{Theres a " << pickable->name(2) << " below me, but I have nothing to grab it with} ";
		return false;
	}

	std::cout << "{picking up a " << pickable->name(2) << " with my empty " << picker->tool->name(0) << "} ";
	return picker->startAttempt(NULL, pickable, NULL);
}
