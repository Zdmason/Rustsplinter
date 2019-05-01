
#include "SpamLevitation.h"

#include "..\..\World.h"

SpamLevitation::SpamLevitation() : Task() {
	taskName="SpamLevitation";
	priority=1;
}


bool SpamLevitation::attempt(Unit* taskMaster) {
	std::vector<Unit*> opponents=World::me->getNearbyUnits(taskMaster->xPos, taskMaster->yPos, taskMaster->zPos, 1.9, true);
	for(unsigned int i=0;i<opponents.size();i++)
	{
		if(opponents[i]->species!=taskMaster->species)
		{
			continue;
		}

		Actool* LEVITUT=taskMaster->getActool("CastLevitation", NULL_ACTION_TAG, NULL_ACTION_SUBTAG, opponents[i], NULL, NULL);

		if(LEVITUT==NULL)
		{
			std::cout << "{Wanted to levitut " << opponents[i]->name(1) << ", but I, " << taskMaster->name(2) << ", don't have the levitut spell?} ";
			World::me->pause();
			return false;
		}

		std::cout << "{Levitooted " << opponents[i]->name(1) << "} ";
		return LEVITUT->startAttempt(opponents[i], NULL, NULL);
	}

	std::cout << "{SpamLevitation had no valid targets} ";
	return false;
}
