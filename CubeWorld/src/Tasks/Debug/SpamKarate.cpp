
#include "SpamKarate.h"

#include "..\..\World.h"

SpamKarate::SpamKarate() : Task() {
	taskName="SpamKarate";
	priority=1;
}


bool SpamKarate::attempt(Unit* taskMaster) {
	std::vector<Unit*> opponents=World::me->getNearbyUnits(taskMaster->xPos, taskMaster->yPos, taskMaster->zPos, 1.9, true);
	for(unsigned int i=0;i<opponents.size();i++)
	{
		if(opponents[i]->species!=taskMaster->species)
		{
			Actool* CAWATICHOP=taskMaster->getActool("DebugKarate", NULL_ACTION_TAG, NULL_ACTION_SUBTAG, opponents[i], NULL, NULL);

			if(CAWATICHOP==NULL)
			{

				std::cout << "{target " << opponents[i]->name(1) << " in range, but can't chop him} ";
				return false;
			}

			std::cout << "{karate'd " << opponents[i]->name(1) << "} ";
			return CAWATICHOP->startAttempt(opponents[i], NULL, NULL);
		}
	}

	std::cout << "{No valid targets to chawp} ";
	return false;
}
