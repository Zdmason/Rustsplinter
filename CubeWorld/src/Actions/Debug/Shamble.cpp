
#include "Shamble.h"
#include "../../World.h"

Shamble::Shamble() : MeleeMovement() {
	actionName="Shamble";

	castpoint=1500;
	backswing=1500;
}


int Shamble::howPossible(Item* tool, Unit* attempter) {
	if(tool==NULL || tool->initStatus==2)
	{
		return -1;
	}

	if(!tool->isManipulatable(attempter))
	{
		return 0;
	}

	if(getSTargets(tool, attempter).empty())
	{
		return 1;
	}

	return 2;
}


std::vector<Item*> Shamble::getTools(Unit* attempter, int possibleLevel) {
	std::vector<Item*> results;

	std::vector<Item*> maybeTools=attempter->getBlob(true, 0, 0, 0, NULL, 0, 0);
	for(unsigned int i=0;i<maybeTools.size();i++)
	{
		if(howPossible(maybeTools[i], attempter)>=possibleLevel)
		{
			results.push_back(maybeTools[i]);
		}
	}

	return results;
}
