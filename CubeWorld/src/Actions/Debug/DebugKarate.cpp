
#include "DebugKarate.h"

#include "../../World.h"

DebugKarate::DebugKarate() : Action() {
	actionName="DebugKarate";
	actionType=COMBAT;

	backswing=1500;
}


int DebugKarate::howPossible(Item* tool, Unit* attempter) {
	if(getUTargets(tool, attempter).empty())
	{
		return 1;
	}

	return 2;
}


std::vector<Item*> DebugKarate::getTools(Unit* attempter, int possibleLevel) {
	std::vector<Item*> nullVec;
	nullVec.push_back(NULL);
	return nullVec;
}

std::vector<Unit*> DebugKarate::getUTargets(Item* tool, Unit* attempter) {
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


bool DebugKarate::attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget) {
	int hit=World::me->random(1, 10);
	if(hit==1)
	{
		std::cout << "[I WHUPPED SOME GUYS ASS AYYYYYYY. push + damage] ";
		uTarget->addGravForce((uTarget->xPos-attempter->xPos)*1000, (uTarget->yPos-attempter->yPos)*1000, 0, attempter, NULL, false);
		uTarget->damage(0, 0, 0, 0, 999, 0, NULL, attempter, false);
	}
	else if(hit<=4)
	{
		std::cout << "[SHORYUKEN! uppercut] ";
		uTarget->addGravForce(0, 0, 8000, attempter, NULL, false);
	}
	else if(hit<=7)
	{
		std::cout << "[HADOUKEN! away blast] ";
		uTarget->addGravForce((uTarget->xPos-attempter->xPos)*1000, (uTarget->yPos-attempter->yPos)*1000, 1000, attempter, NULL, false);
	}
	else if(hit<=8)
	{
		std::cout << "[FALCO- PAWNCH! away superslam] ";
		uTarget->addGravForce((uTarget->xPos-attempter->xPos)*20000, (uTarget->yPos-attempter->yPos)*20000, 20000, attempter, NULL, false);
	}
	else
	{
		std::cout << "[ORAAAAAAA! down slam] ";
		uTarget->addGravForce(0, 0, -10000, attempter, NULL, false);
	}

	return true;
}
