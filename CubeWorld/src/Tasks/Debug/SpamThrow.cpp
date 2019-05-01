
#include "SpamThrow.h"

#include "..\..\World.h"

SpamThrow::SpamThrow() : Task() {
	taskName="SpamThrow";
	priority=1;
}


bool SpamThrow::attempt(Unit* taskMaster) {
	Actool* nextMove=taskMaster->getActool("Throw", NULL_ACTION_TAG, NULL_ACTION_SUBTAG, 2);
	if(nextMove==NULL)
	{
		if(World::me->getNearbyUnits(taskMaster->xPos, taskMaster->yPos, taskMaster->zPos, 5.0, true).size()<2)
		{
			std::cout << "{Nobody to throw at} ";
			return false;
		}

		std::vector<Item*> grabbable=taskMaster->getBlob(false, -1, 0, 0, NULL, 0, 0);

		if(grabbable.empty())
		{
			std::cout << "{nothing to grab for spamthrow} ";
			return false;
		}

		nextMove=taskMaster->getActool("", GRAB, NULL_ACTION_SUBTAG, NULL, grabbable.front(), NULL);
		if(nextMove==NULL)
		{
			std::cout << "{nothing to grab / throw} ";
			return false;
		}

		std::cout << "{taking out a " << grabbable.front()->name(2) << " to throw} ";
		nextMove->startAttempt(NULL, grabbable.front(), NULL);
		return true;
	}

	std::vector<Unit*> opponents=nextMove->getUTargets();
	for(unsigned int i=0;i<opponents.size();i++)
	{
		if(opponents[i]->species!=taskMaster->species)
		{
			std::cout << "{chucking a " << nextMove->tool->name(0) << " at " << opponents[i]->name(2) << "} ";
			nextMove->startAttempt(opponents[i], NULL, NULL);
			return true;
		}
	}

	std::cout << "{SpamThrow had something to throw but nobody to throw it at} ";
	return false;
}
