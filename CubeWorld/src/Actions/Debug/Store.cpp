
#include "Store.h"

#include "../../World.h"

Store::Store() : Action() {
	// Store: tool = a hand holding an object to be stored, iTarget = the thing we're storing stuff into

	actionName="Store";
	actionType=STORE;
}


int Store::howPossible(Item* tool, Unit* attempter) {
	if(tool==NULL || tool->initStatus==2)
	{
		return -1;
	}

	if(tool->selfTags.count(HANDLIKE)==0)
	{
		return -1;
	}

	if(tool->holding==NULL)
	{
		return 0;
	}

	if(!tool->isManipulatable(attempter))
	{
		return 0;
	}

	if(getITargets(tool, attempter).empty())
	{
		return 1;
	}

	return 2;
}


std::vector<Item*> Store::getTools(Unit* attempter, int possibleLevel) {
	std::vector<Item*> results;

	std::vector<Item*> maybeTools=attempter->getParts("", HANDLIKE, true, 0, 0, 0, NULL, 0, 0);
	for(unsigned int i=0;i<maybeTools.size();i++)
	{
		if(howPossible(maybeTools[i], attempter)>=possibleLevel)
		{
			results.push_back(maybeTools[i]);
		}
	}

	return results;
}

std::vector<Item*> Store::getITargets(Item* tool, Unit* attempter) {
	std::vector<Item*> results;

	std::vector<Item*> possibleTargets=World::me->getNearbyItems(attempter->xPos, attempter->yPos, attempter->zPos, 1.9, true, 1, NULL);
	for(unsigned int i=0;i<possibleTargets.size();i++)
	{
		if(possibleTargets[i]->species=="RoboPack") // TODO: any item with storage space that accepts things of our held objects type (can't store arms in a bun, but can with bullets)
		{
			results.push_back(possibleTargets[i]);
		}
	}
	return results;
}


bool Store::attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget) {
	if(howPossible(tool, attempter)<2)
	{
		std::cout << "Store action attempting but howposible with tool/user " << tool->name(2) << " " << attempter->name(2) << " is only " << howPossible(tool, attempter);
		World::me->pause();
		return false;
	}

	iTarget->store(tool->holding, true);

	if(tool->holding!=NULL)
	{
		std::cout << "store commanded something, but its still holding something?";
		World::me->pause();
	}

	return true;
}
