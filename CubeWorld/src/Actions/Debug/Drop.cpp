
#include "Drop.h"

#include "../../World.h"

Drop::Drop() : Action() {
	actionName="Drop";
	actionType=DROP;
}


int Drop::howPossible(Item* tool, Unit* attempter) {
	if(tool==NULL || tool->initStatus==2)
	{
		return -1;
	}

	if(tool->selfTags.count(HANDLIKE)==0)
	{
		if(tool->holding!=NULL)
		{
			std::cout << "Drop howPossible detected " << tool->name(2) <<  " holding something, but its not handlike?";
			World::me->pause();
			return -666;
		}

		return -1;
	}

	if(tool->holding==NULL)
	{
		return 0;
	}

	if(tool->owner==NULL)
	{
		std::cout << "Drop action detected " << tool->name(2) <<  " holding something, but its carrystatus aint organ?";
		World::me->pause();
		return -666;
	}

	if(!tool->isManipulatable(attempter))
	{
		return 0;
	}

	return 2;
}


std::vector<Item*> Drop::getTools(Unit* attempter, int possibleLevel) {
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

std::vector<Item*> Drop::getITargets(Item* tool, Unit* attempter) {
	std::vector<Item*> heldThing;

	if(tool==NULL)
	{
		std::cout << "Drop iTargets given a null tool?";
		World::me->pause();
		return heldThing;
	}

	if(tool->holding==NULL)
	{
		std::cout << "Drop iTargets detected " << tool->name(2) <<  " not holding anything?";
		World::me->pause();
		return heldThing;
	}

	heldThing.push_back(tool->holding);
	return heldThing;
}


bool Drop::attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget) {

	tool->drop(true);

	if(tool->holding==NULL)
	{
		;
	}
	else
	{
		std::cout << "drop commanded something, but its still holding something?";
		World::me->pause();
	}

	return true;
}
