
#include "Throw.h"

#include "../../World.h"

Throw::Throw() : Action() {
	// TOOL is the thing being thrown, NOT the arm we're throwing it with
	actionName="Throw";
	actionType=GRAB;
}


int Throw::howPossible(Item* tool, Unit* attempter) {
	if(tool==NULL || tool->initStatus==2)
	{
		return -1;
	}

	if(tool->holders.empty())
	{
		return 0;
	}

	if(attempter->connected(tool, 1, 3, 0, 3))
	{
		return 0;
	}

	if(tool->allCarryStati(attempter).count(HELD)==0)
	{
		return 0;
	}

	// TODO: arm strength, aka can't throw a full unit / blob unless you're strong enough
	// If we CAN throw it, we throw at full strength

	if(tool->getBlob(1, 3, 3, 3, attempter, -4, 0).size()!=1)
	{
		std::cout << "size is " << tool->holding->getBlob(1, 3, 3, 3, attempter, -4, 0).size() << std::endl;
		return 0;
	}

	if(getITargets(tool, attempter).empty())
	{
		return 1;
	}

	return 2;
}


std::vector<Item*> Throw::getTools(Unit* attempter, int possibleLevel) {
	std::vector<Item*> results;

	std::vector<Item*> maybeTools=attempter->getParts("", NULL_ITEM_TAG, false, 0, -1, 0, attempter, 1, 2);
	for(unsigned int i=0;i<maybeTools.size();i++)
	{
		if(howPossible(maybeTools[i], attempter)>=possibleLevel)
		{
			results.push_back(maybeTools[i]);
		}
	}

	return results;
}

std::vector<Item*> Throw::getITargets(Item* tool, Unit* attempter) {
	std::vector<Item*> results;

	// TODO: range is based on how far we can throw it with: int bestStr=tool->strengthLevel(attempter);

	std::vector<Item*> possibleTargets=World::me->getNearbyItems(attempter->xPos, attempter->yPos, attempter->zPos, 5.0, true, 1, NULL);
	for(unsigned int i=0;i<possibleTargets.size();i++)
	{
		if(possibleTargets[i]->xPos!=attempter->xPos || possibleTargets[i]->yPos!=attempter->yPos || possibleTargets[i]->zPos!=attempter->zPos)
		{
			results.push_back(possibleTargets[i]);
		}
	}

	return results;
}

std::vector<Unit*> Throw::getUTargets(Item* tool, Unit* attempter) {
	std::vector<Unit*> results;

	// TODO: range is based on how far we can throw it with: int bestStr=tool->strengthLevel(attempter);

	std::vector<Unit*> possibleTargets=World::me->getNearbyUnits(attempter->xPos, attempter->yPos, attempter->zPos, 5.0, true);
	for(unsigned int i=0;i<possibleTargets.size();i++)
	{
		if(possibleTargets[i]->xPos!=attempter->xPos || possibleTargets[i]->yPos!=attempter->yPos || possibleTargets[i]->zPos!=attempter->zPos)
		{
			results.push_back(possibleTargets[i]);
		}
	}

	return results;
}

std::vector<Square*> Throw::getSTargets(Item* tool, Unit* attempter) {
	std::vector<Square*> results;

	// TODO: range is based on how far we can throw it with: int bestStr=tool->strengthLevel(attempter);

	std::vector<Square*> possibleTargets=World::me->getNearbySquares(attempter->xPos, attempter->yPos, attempter->zPos, 5.0, true);
	for(unsigned int i=0;i<possibleTargets.size();i++)
	{
		if(possibleTargets[i]->xPos!=attempter->xPos || possibleTargets[i]->yPos!=attempter->yPos || possibleTargets[i]->zPos!=attempter->zPos)
		{
			results.push_back(possibleTargets[i]);
		}
	}

	return results;
}


int Throw::getValue(Item* tool, Unit* attempter) {
	if(tool==NULL)
	{
		return -1;
	}

	return std::min(10000, tool->strengthLevel(attempter)*1000/tool->totalWeight()); // TODO: instead, damage value we'd expect from this hitting the target
}


bool Throw::attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget) {
	if(howPossible(tool, attempter)<2)
	{
		std::cout << "Throw action attempting but howposible with tool/user " << tool->name(2) << " " << attempter->name(2) << " is only " << howPossible(tool, attempter);
		World::me->pause();
		return false;
	}

	int velocity=std::min(10000, tool->strengthLevel(attempter)*1000);

	int result=-666;

	if(uTarget!=NULL)
	{
		result=tool->throwAt(uTarget, -1, -1, -1, velocity);
	}
	else if(iTarget!=NULL)
	{
		result=tool->throwAt(iTarget, -1, -1, -1, velocity);
	}
	else if(sTarget!=NULL)
	{
		result=tool->throwAt(NULL, sTarget->xPos, sTarget->yPos, sTarget->zPos, velocity);
	}
	else
	{
		std::cout << tool->name(2) << " how the fuck did we get ehre at throw attempt??";
		World::me->pause();
	}

	if(result<0)
	{
		std::cout << tool->name(2) << " threw at a target, but it failed?";
		World::me->pause();
	}

	return true;
}
