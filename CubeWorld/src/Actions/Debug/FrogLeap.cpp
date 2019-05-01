
#include "FrogLeap.h"

#include "../../World.h"

FrogLeap::FrogLeap() : Action() {
	actionName="FrogLeap";
	actionType=MISC;
}


int FrogLeap::howPossible(Item* tool, Unit* attempter) {
	if(tool==NULL || tool->initStatus==2)
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

	return 2;
}


std::vector<Item*> FrogLeap::getTools(Unit* attempter, int possibleLevel) {
	std::vector<Item*> results;

	std::vector<Item*> possibleTools=attempter->getParts("", LEGLIKE, true, 0, 0, 0, NULL, 0, 0);
	for(unsigned int i=0;i<possibleTools.size();i++)
	{
		if(howPossible(possibleTools[i], attempter)>=possibleLevel)
		{
			results.push_back(possibleTools[i]);
		}
	}
	return results;
}

std::vector<Square*> FrogLeap::getSTargets(Item* tool, Unit* attempter) {
	std::vector<Square*> results;

	std::queue<Square*> possibleTargets=World::me->getNear(attempter->xPos, attempter->yPos, attempter->zPos);
	while(!possibleTargets.empty())
	{
		if(possibleTargets.front()->zPos==attempter->zPos && (possibleTargets.front()->xPos!=attempter->xPos || possibleTargets.front()->yPos!=attempter->yPos))
		{
			results.push_back(possibleTargets.front());
		}

		possibleTargets.pop();
	}

	return results;
}


bool FrogLeap::attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget) {
	if(sTarget->xPos<=0 || sTarget->xPos>=World::me->xMax || sTarget->yPos<=0 || sTarget->yPos>=World::me->yMax || sTarget->zPos<=0 || sTarget->zPos>=World::me->zMax)
	{
		return -1;
	}

	int xDir=0;
	if(sTarget->xPos>attempter->xPos)
	{
		xDir=1;
	}
	else if(sTarget->xPos<attempter->xPos)
	{
		xDir=-1;
	}

	int yDir=0;
	if(sTarget->yPos>attempter->yPos)
	{
		yDir=1;
	}
	else if(sTarget->yPos<attempter->yPos)
	{
		yDir=-1;
	}

	attempter->addGravForce(xDir*2000, yDir*2000, 5000, attempter, NULL, false);
	std::cout << "[I leapt into the air in the xy : " << xDir << " " << yDir << " direction] ";

	return true;
}

