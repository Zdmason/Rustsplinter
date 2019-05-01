
#include "MeleeAttack.h"

#include "../../../World.h"

MeleeAttack::MeleeAttack(std::string myName, int myImpactScale, int mySlashScale, int mySlashMax, int myStabScale, int myStabMax, int myBrokeDamage, int myMaxDamage, int mySoulDamage) : Action() {
	actionName="MeleeAttack"; // int myBroke, int myImpact, int mySlash, int myStab, int myMax, int mySoul
	actionType=COMBAT;
	actionSubtype=MELEE;

	name=myName;
	impactScale=myImpactScale;
	slashScale=mySlashScale;
	slashMax=mySlashMax;
	stabScale=myStabScale;
	stabMax=myStabMax;
	brokeDamage=myBrokeDamage;
	maxDamage=myMaxDamage;
	soulDamage=mySoulDamage;
}


int MeleeAttack::howPossible(Item* tool, Unit* attempter) {
	if(tool==NULL || tool->initStatus==2)
	{
		return -1;
	}

	if(!tool->isUseable(attempter) || !tool->isActive())
	{
		return 0;
	}

	// TODO: minimum weight requirements, that can adjust on the fly if weight is increased / decreased?

	if(getITargets(tool, attempter).empty())
	{
		return 1;
	}

	return 2;
}


std::vector<Item*> MeleeAttack::getTools(Unit* attempter, int possibleLevel) {
	std::vector<Item*> results;

	std::vector<Item*> maybeTools=attempter->getBlob(true, 0, -1, 0, NULL, 0, 0); // TODO: all useable, even if its another unit's fist? or handled in the search / what's usable
	for(unsigned int i=0;i<maybeTools.size();i++)
	{
		results.push_back(maybeTools[i]);
	}

	return results;
}

std::vector<Item*> MeleeAttack::getITargets(Item* tool, Unit* attempter) {
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

std::vector<Unit*> MeleeAttack::getUTargets(Item* tool, Unit* attempter) {
	std::vector<Unit*> results;

	std::vector<Unit*> opponents=World::me->getNearbyUnits(attempter->xPos, attempter->yPos, attempter->zPos, 1.9, true);
	for(unsigned int i=0;i<opponents.size();i++)
	{
		results.push_back(opponents[i]);
	}
	return results;
}


int MeleeAttack::getValue(Item* tool, Unit* attempter) {
	if(tool==NULL)
	{
		return -1;
	}

	int str=tool->strengthLevel(attempter); // TODO: change impact damage to its lesser form, or it will overtake slash / stab damage by like 10k
	return (impactScale*str*tool->weight/World::me->forcePerDamage)+std::min(slashScale*str, slashMax)+std::min(stabScale*str, stabMax)+brokeDamage+maxDamage+soulDamage;
}


bool MeleeAttack::attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget) {
	int str=tool->strengthLevel(attempter);

	if(uTarget!=NULL)
	{
		std::cout << "[Meleed " << uTarget->name(1) << " with " << tool->name(0) << " for " << getValue(tool, attempter) << " damage] ";
		uTarget->damage((impactScale*str*tool->weight/World::me->forcePerDamage), std::min(slashScale*str, slashMax), std::min(stabScale*str, stabMax), brokeDamage, maxDamage, soulDamage, tool, attempter, false);
	}
	else if(iTarget!=NULL)
	{
		std::cout << "[Aim meleed " << iTarget->name(2) << " with " << tool->name(0) << " for " << getValue(tool, attempter) << " damage] ";
		iTarget->damage((impactScale*str*tool->weight/World::me->forcePerDamage), std::min(slashScale*str, slashMax), std::min(stabScale*str, stabMax), brokeDamage, maxDamage, soulDamage, tool, attempter, false);
	}
	else
	{
		std::cout << "MeleeAttack action needs a target?";
		World::me->pause();
		return false;
	}

	return true;
}
