
#include "SpamMelee.h"

#include "..\..\World.h"

SpamMelee::SpamMelee() : Task() {
	taskName="SpamMelee";
	priority=1;
}


bool SpamMelee::attempt(Unit* taskMaster) {
	std::vector<Unit*> opponents=World::me->getNearbyUnits(taskMaster->xPos, taskMaster->yPos, taskMaster->zPos, 1.9, true);
	for(unsigned int i=0;i<opponents.size();i++)
	{
		if(opponents[i]->species=="PickupBot" || opponents[i]->species==taskMaster->species)
		{
			continue;
		}

		Actool* possibleAttack=taskMaster->getActool("", COMBAT, MELEE, opponents[i], NULL, NULL);

		if(possibleAttack==NULL)
		{
			std::cout << "{no attacks to spammelee with} ";
			return false;
		}

		std::cout << "{swung at " << opponents[i]->name(1) << "} ";
		possibleAttack->startAttempt(opponents[i], NULL, NULL);
		return true;
	}

	std::cout << "{no valid targets to spammelee} ";
	return false;
}
