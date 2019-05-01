
#include "CastLevitation.h"

#include "../../World.h"
#include "../../Stati/Physical/Levitation.h"

CastLevitation::CastLevitation() : Action() {
	actionName="CastLevitation";
	actionType=COMBAT;
}


int CastLevitation::howPossible(Item* tool, Unit* attempter) {
	if(getITargets(tool, attempter).empty() && getUTargets(tool, attempter).empty())
	{
		return 1;
	}

	return 2;
}


std::vector<Item*> CastLevitation::getTools(Unit* attempter, int possibleLevel) {
	std::vector<Item*> nullVec;
	nullVec.push_back(NULL);
	return nullVec;
}

std::vector<Item*> CastLevitation::getITargets(Item* tool, Unit* attempter) {
	std::vector<Item*> results;

	std::vector<Item*> possibleTargets=World::me->getNearbyItems(attempter->xPos, attempter->yPos, attempter->zPos, 1.9, true, 1, NULL);
	for(unsigned int i=0;i<possibleTargets.size();i++)
	{
		results.push_back(possibleTargets[i]);
	}
	return results;
}

std::vector<Unit*> CastLevitation::getUTargets(Item* tool, Unit* attempter) {
	std::vector<Unit*> results;

	std::vector<Unit*> possibleTargets=World::me->getNearbyUnits(attempter->xPos, attempter->yPos, attempter->zPos, 1.9, true);
	for(unsigned int i=0;i<possibleTargets.size();i++)
	{
		results.push_back(possibleTargets[i]);
	}
	return results;
}


bool CastLevitation::attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget) {

	std::cout << "[Cast levitation on " << uTarget->name(1) <<  "] ";
	uTarget->addGravForce(0, 0, 1000, attempter, NULL, false);
	World::me->addStatus(new Levitation(5), uTarget, false);

	return true;
}

