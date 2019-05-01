
#include "GrabAnyUnit.h"

#include "..\..\World.h"

GrabAnyUnit::GrabAnyUnit() : Task() {
	taskName="GrabAnyUnit";
	priority=1;
}


bool GrabAnyUnit::attempt(Unit* taskMaster) {
	std::vector<Unit*> grabables=World::me->getNearbyUnits(taskMaster->xPos, taskMaster->yPos, taskMaster->zPos, 1.9, true);
	if(grabables.size()<2)
	{
		std::cout << "{noboby else grabbable near me} ";
		return false;
	}

	for(unsigned int i=0;i<grabables.size();i++)
	{
		if(grabables[i]->id!=taskMaster->id)
		{
			Actool* grabber=taskMaster->getActool("", GRAB, NULL_ACTION_SUBTAG, NULL, grabables[i]->brain, NULL);

			if(grabber!=NULL)
			{
				std::cout << "{grabbing " << grabables[i]->name(1) << " by the " << grabables[i]->brain->name(0) << " with my " << grabber->tool->name(0) << "} ";
				return grabber->startAttempt(NULL, grabables[i]->brain, NULL);
			}
		}
	}

	std::cout << "{no valid targets to grab?} ";
	return false;
}
