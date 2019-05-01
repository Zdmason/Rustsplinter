
#include "Shoot.h"

#include "../../World.h"
#include "../../Entities/Items/Archetypes/Gunlike.h"

Shoot::Shoot() : Action() {
	actionName="Shoot";
	actionType=COMBAT;
}


int Shoot::howPossible(Item* tool, Unit* attempter) {
	if(tool==NULL || tool->initStatus==2)
	{
		return -1;
	}

	if(tool->selfTags.count(GUNLIKE)==0)
	{
		return -1;
	}

	if(tool->storing.empty())
	{
		return 0;
	}

	if(!tool->isUseable(attempter) || !tool->isActive())
	{
		return 0;
	}

	if(tool->count("", BULLETLIKE, 0, -1, 0, 0, NULL, 0, 0)==0) // TODO: only the specific type of bullet the gun uses
	{
		return 0;
	}

	if(getITargets(tool, attempter).empty())
	{
		return 1;
	}

	return 2;
}


std::vector<Item*> Shoot::getTools(Unit* attempter, int possibleLevel) {
	std::vector<Item*> results;

	std::vector<Item*> maybeTools=attempter->getParts("", GUNLIKE, true, 0, -1, 0, NULL, 0, 0);
	for(unsigned int i=0;i<maybeTools.size();i++)
	{
		if(howPossible(maybeTools[i], attempter)>=possibleLevel)
		{
			results.push_back(maybeTools[i]);
		}
	}

	return results;
}

std::vector<Item*> Shoot::getITargets(Item* tool, Unit* attempter) { // TODO: check gunlike for its range, which should be the range below
	std::vector<Item*> results;

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

std::vector<Unit*> Shoot::getUTargets(Item* tool, Unit* attempter) {
	std::vector<Unit*> results;

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

std::vector<Square*> Shoot::getSTargets(Item* tool, Unit* attempter) {
	std::vector<Square*> results;

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


int Shoot::getValue(Item* tool, Unit* attempter) {
	if(tool==NULL || tool->selfTags.count(GUNLIKE)==0)
	{
		return -1;
	}

	Gunlike* gunner=dynamic_cast<Gunlike*>(tool);

	return gunner->shootDamage;
}


bool Shoot::attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget) {
	// TODO: gun gets jammed if it has wrong bullet type?

	Entity* realTarget;

	if(uTarget!=NULL)
	{
		realTarget=World::me->tryTargetTo(attempter->xPos, attempter->yPos, attempter->zPos, uTarget->xPos, uTarget->yPos, uTarget->zPos, true, 1);
		if(realTarget==NULL)
		{
			realTarget=uTarget;
		}
	}
	else if(iTarget!=NULL)
	{
		realTarget=World::me->tryTargetTo(attempter->xPos, attempter->yPos, attempter->zPos, iTarget->xPos, iTarget->yPos, iTarget->zPos, true, 1);
		if(realTarget==NULL)
		{
			realTarget=iTarget;
		}
	}
	else if(sTarget!=NULL)
	{
		realTarget=World::me->tryTargetTo(attempter->xPos, attempter->yPos, attempter->zPos, sTarget->xPos, sTarget->yPos, sTarget->zPos, true, 1);
		if(realTarget==NULL)
		{
			// TODO: we shoot past the square in the same direction?
			return -666;
		}
	}
	else
	{
		std::cout << tool->name(2) << " how the fuck did we get ehre at shoot attempt??";
		World::me->pause();
	}

	std::cout << tool->name(2) << " shot a bullet at " << realTarget->name(0);
	World::me->remItem(tool->getPart("", BULLETLIKE, 0, -1, 0, 0, NULL, 0, 0));
	// TODO: remove a random bullet instead?
	// TODO: some bullets embed? some set target on fire? custom function here to decide what happens to fired bullets?

	Gunlike* gunner=dynamic_cast<Gunlike*>(tool);
	realTarget->damage(0, 0, gunner->shootDamage, 0, 0, 0, tool, attempter, false); // TODO: gun + bullet damage here, also what type of damage?

	return true;
}
