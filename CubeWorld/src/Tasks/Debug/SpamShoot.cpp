
#include "SpamShoot.h"

#include "..\..\World.h"

SpamShoot::SpamShoot() : Task() {
	taskName="SpamShoot";
	priority=1;
}


bool SpamShoot::attempt(Unit* taskMaster) {
	Actool* nextMove=taskMaster->getActool("Shoot", NULL_ACTION_TAG, NULL_ACTION_SUBTAG, 2);
	if(nextMove==NULL)
	{
		std::cout << "{ran out of ammo / targets to spamshoot} ";
		return false;
	}

	std::vector<Unit*> opponents=nextMove->getUTargets();
	for(unsigned int i=0;i<opponents.size();i++)
	{
		if(opponents[i]->species!=taskMaster->species)
		{
			std::cout << "{shooting my " << nextMove->tool->name(0) << " at " << opponents[i]->name(0) << "} ";
			return nextMove->startAttempt(opponents[i], NULL, NULL);;
		}
	}

	std::cout << "{SpamShoot had something to shoot but nobody to aim it at?} ";
	return false;
}
