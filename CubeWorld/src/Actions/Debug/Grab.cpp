
#include "Grab.h"

#include "../../World.h"

Grab::Grab() : Action() {
	actionName="Grab";
	actionType=GRAB;
}


int Grab::howPossible(Item* tool, Unit* attempter) {
	if(tool==NULL || tool->initStatus==2)
	{
		return -1;
	}

	if(tool->selfTags.count(HANDLIKE)==0)
	{
		return -1;
	}

	if(tool->holding!=NULL)
	{
		return 0;
	}

	if(!tool->isManipulatable(attempter))
	{
		return 0;
	}

	// TODO: weight requirement based on strength

	if(getITargets(tool, attempter).empty())
	{
		return 1;
	}

	return 2;
}


std::vector<Item*> Grab::getTools(Unit* attempter, int possibleLevel) {
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

std::vector<Item*> Grab::getITargets(Item* tool, Unit* attempter) {
	std::vector<Item*> results;

	// TODO: grab strength: a hand can only grab a thing if the size of its parts <= its strength

	std::vector<Item*> possibleTargets=World::me->getNearbyItems(attempter->xPos, attempter->yPos, attempter->zPos, 1.9, true, 1, NULL);
	for(unsigned int i=0;i<possibleTargets.size();i++)
	{
		results.push_back(possibleTargets[i]);
	}

	possibleTargets=attempter->getBlob(false, -1, 0, 0, NULL, 0, 0);
	for(unsigned int i=0;i<possibleTargets.size();i++)
	{
		results.push_back(possibleTargets[i]);
	}

	return results;
}

std::vector<Unit*> Grab::getUTargets(Item* tool, Unit* attempter) {
	std::vector<Unit*> results;

	std::vector<Unit*> possibleTargets=World::me->getNearbyUnits(attempter->xPos, attempter->yPos, attempter->zPos, 1.9, true);
	for(unsigned int i=0;i<possibleTargets.size();i++)
	{
		if(possibleTargets[i]->id!=attempter->id)
		{
			results.push_back(possibleTargets[i]);
		}
	}
	return results;
}


bool Grab::attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget) {
	tool->grab(iTarget, true);

	if(tool->holding==iTarget)
	{
		std::cout << "Grabbed " << iTarget->name(2) << " with my " << tool->name(2);
	}
	else
	{
		std::cout << "Grab commanded something, but i'm not holding it now?";
		World::me->pause();
	}

	return true;
}
