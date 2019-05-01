
#include "MeleeMovement.h"
#include "..\..\World.h"

MeleeMovement::MeleeMovement() : Movement() {
	actionName="Walk";
	actionType=MOVEMENT;
	actionSubtype=WALK;
}


int MeleeMovement::howPossible(Item* tool, Unit* attempter) {
	// Standard movement = has 2 legs, both must be active / manipulable

	if(tool==NULL)
	{
		return -1;
	}

	if(tool->selfTags.count(LEGLIKE)==0)
	{
		return -1;
	}

	if(!tool->isManipulatable(attempter))
	{
		return 0;
	}

	if(attempter->count("", LEGLIKE, true, 0, 0, 0, attempter, 0, 3)<2)
	{
		return 0;
	}

	if(getSTargets(tool, attempter).empty())
	{
		return 1;
	}

	return 2;
}


std::vector<Item*> MeleeMovement::getTools(Unit* attempter, int possibleLevel) {
	std::vector<Item*> results;

	std::vector<Item*> maybeTools=attempter->getParts("", LEGLIKE, true, 0, 0, 0, NULL, 0, 0);
	for(unsigned int i=0;i<maybeTools.size();i++)
	{
		if(howPossible(maybeTools[i], attempter)>=possibleLevel)
		{
			results.push_back(maybeTools[i]);
		}
	}

	return results;
}

std::vector<Square*> MeleeMovement::getSTargets(Item* tool, Unit* attempter) {
	std::vector<Square*> results;

	std::queue<Square*> possibleTargets=World::me->getNear(attempter->xPos, attempter->yPos, attempter->zPos);
	while(!possibleTargets.empty())
	{
		if(attempter->canRiskwalk(World::me->cube[attempter->xPos][attempter->yPos][attempter->zPos], possibleTargets.front())==0)
		{
			results.push_back(possibleTargets.front());
		}

		possibleTargets.pop();
	}

	return results;
}


bool MeleeMovement::couldAttempt(Item* tool, Unit* attempter, Square* fakeStart, Square* fakeEnd, bool risky) {
	return risky ? attempter->canRiskwalk(fakeStart, fakeEnd) : attempter->canWalk(fakeStart, fakeEnd);
}

bool MeleeMovement::attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget) {
	// TODO: step forward with tool, so if you land in a freezing trap or whatever that foot tool takes the hit first

	int result=attempter->tryMove(sTarget->xPos, sTarget->yPos, sTarget->zPos, NULL, true, getActool(tool, attempter, 2), attempter);

	if(result>=0)
	{
		std::cout << "[ " << actionName << " move to " << sTarget->xPos << " " << sTarget->yPos << "] ";
	}
	else
	{
		std::cout << actionName << " action attempting to move but howposible with tool/user " << tool->name(2) << " " << attempter->name(2) << " passed but we failed anyways? ";
		World::me->pause();
	}

	return result>=0;
}
