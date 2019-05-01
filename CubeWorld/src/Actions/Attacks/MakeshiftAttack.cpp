
#include "MakeshiftAttack.h"

#include "../../World.h"

MakeshiftAttack::MakeshiftAttack() : Action() {
	actionName="MeleeAttack";
	actionType=COMBAT;
	actionSubtype=MELEE;
}


int MakeshiftAttack::howPossible(Item* tool, Unit* attempter) {
	if(tool==NULL || tool->initStatus==2)
	{
		return -1;
	}

	if(!tool->isUseable(attempter))
	{
		return 0;
	}

	if(getITargets(tool, attempter).empty())
	{
		return 1;
	}

	return 2;
}


std::vector<Item*> MakeshiftAttack::getTools(Unit* attempter, int possibleLevel) {
	std::vector<Item*> results;

	std::vector<Item*> maybeTools=attempter->getBlob(true, 0, -1, 0, NULL, 0, 0); // TODO: all useable, even if its another unit's fist? or handled in the search / what's usable
	for(unsigned int i=0;i<maybeTools.size();i++)
	{
		results.push_back(maybeTools[i]);
	}

	return results;
}

std::vector<Item*> MakeshiftAttack::getITargets(Item* tool, Unit* attempter) {
	std::vector<Item*> results;

	std::vector<Item*> opponents=World::me->getNearbyItems(attempter->xPos, attempter->yPos, attempter->zPos, 1.9, true, 1, NULL);
	for(unsigned int i=0;i<opponents.size();i++)
	{
		if(opponents[i]->id!=attempter->id) // TODO: we can grab our own parts too, just no use cases yet
		{
			results.push_back(opponents[i]);
		}
	}
	return results;
}

std::vector<Unit*> MakeshiftAttack::getUTargets(Item* tool, Unit* attempter) {
	std::vector<Unit*> results;

	std::vector<Unit*> opponents=World::me->getNearbyUnits(attempter->xPos, attempter->yPos, attempter->zPos, 1.9, true);
	for(unsigned int i=0;i<opponents.size();i++)
	{
		results.push_back(opponents[i]);
	}
	return results;
}


int MakeshiftAttack::getValue(Item* tool, Unit* attempter) {
	if(tool==NULL)
	{
		return -1;
	}

	int bestStr=tool->strengthLevel(attempter); // TODO: wat here?
	return bestStr*1000*tool->weight/World::forcePerDamage; // TODO: makeshift attacks still do some slash/stab damage based on attack types? same as collide?
}


bool MakeshiftAttack::attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget) {
	int bestStr=getValue(tool, attempter);

	if(uTarget!=NULL)
	{
		std::cout << "[Makeshifted " << uTarget->name(1) << " with " << tool->name(0) << " for " << bestStr*1000*tool->weight/World::forcePerDamage << " hp] ";
		uTarget->damage(bestStr*1000*tool->weight/World::forcePerDamage, 0, 0, 0, 0, 0, tool, attempter, true); // TODO: damage depends on strength of user
	}
	else if(iTarget!=NULL)
	{
		std::cout << "[Aim MakeshiftAttack " << iTarget->name(2) << " with " << tool->name(0) << " for " << bestStr*1000*tool->weight/World::forcePerDamage << " hp] ";
		iTarget->damage(bestStr*1000*tool->weight/World::forcePerDamage, 0, 0, 0, 0, 0, tool, attempter, true);
	}
	else
	{
		std::cout << "MakeshiftAttack action needs a target?";
		World::me->pause();
		return false;
	}

	return true;
}
