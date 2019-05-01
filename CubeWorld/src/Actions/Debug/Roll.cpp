
#include "Roll.h"
#include "..\..\World.h"

Roll::Roll() : MeleeMovement() {
	actionName="Roll";
}


int Roll::howPossible(Item* tool, Unit* attempter) {
	if(tool==NULL || tool->initStatus==2)
	{
		return -1;
	}

	if(tool->species!="WalkerBall")
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


std::vector<Item*> Roll::getTools(Unit* attempter, int possibleLevel) {
	std::vector<Item*> results;

	std::vector<Item*> maybeTools=attempter->getParts("WalkerBall", NULL_ITEM_TAG, true, 0, 0, 0, NULL, 0, 0);
	for(unsigned int i=0;i<maybeTools.size();i++)
	{
		if(howPossible(maybeTools[i], attempter)>=possibleLevel)
		{
			results.push_back(maybeTools[i]);
		}
	}

	return results;
}

std::vector<Square*> Roll::getSTargets(Item* tool, Unit* attempter) {
	// We can't roll uphill, so only same z or lower
	// TODO: can't climb things either like ladders
	// TODO: can roll uphill on flat surfaces

	std::vector<Square*> results;

	std::queue<Square*> possibleTargets=World::me->getNear(attempter->xPos, attempter->yPos, attempter->zPos);
	while(!possibleTargets.empty())
	{
		if(attempter->zPos>=possibleTargets.front()->zPos &&
			attempter->canRiskwalk(World::me->cube[attempter->xPos][attempter->yPos][attempter->zPos], possibleTargets.front())==0)
		{
			results.push_back(possibleTargets.front());
		}

		possibleTargets.pop();
	}

	return results;
}


bool Roll::couldAttempt(Item* tool, Unit* attempter, Square* fakeStart, Square* fakeEnd, bool risky) {
	return fakeStart->zPos>=fakeEnd->zPos && (
			(risky && attempter->canRiskwalk(fakeStart, fakeEnd)==0) ||
			(!risky && attempter->canWalk(fakeStart, fakeEnd)==0));
}
