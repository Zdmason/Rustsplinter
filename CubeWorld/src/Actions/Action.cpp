
#include "Action.h"
#include "Actool.h"
#include "..\World.h"

Action::Action() {
	id=World::me->curId;
	World::me->curId++;

	actionName="Action";
	actionType=NULL_ACTION_TAG;
	actionSubtype=NULL_ACTION_SUBTAG;

	castpoint=500;
	backswing=500;
}

Action::~Action() {
//	; // TODO: make this / replace die()?
}

void Action::cloneTo(Item* obj, Unit* guy, bool selfOnly) {
	std::cout << "Action " << actionName << " needs its cloneTo made";
	World::me->pause();


//	obj->addedActions.push_back(new Whatever(this));
}


Actool* Action::getActool(Item* tool, Unit* attempter, int possibleLevel) {
	// tool can be NULL, in the case we have an action that doesn't require a tool (PK Fire or something)
	// If we explicitly don't need an item, we should return NULL if we get any item for obj as we do manual checks for NULL wherever we search
	// Returns this as an actool, only if possible to actually use it for its purpose in any way (AKA: melee attacks work and return even if we can only hit ourselves, which tends to be always)

	if(howPossible(tool, attempter)<possibleLevel)
	{
		return NULL;
	}

	return new Actool(this, tool, attempter);
}

std::vector<Actool*> Action::getActools(Unit* attempter, int possibleLevel) {
	// Returns all possible actools with this action for the given user, including NULL actools too. If none are possible, an empty vector

	std::vector<Actool*> possibleActools;

	std::vector<Item*> myTools=getTools(attempter, possibleLevel);
	for(unsigned int i=0;i<myTools.size();i++)
	{
		possibleActools.push_back(new Actool(this, myTools[i], attempter));
	}

	return possibleActools;
}


int Action::howPossible(Item* tool, Unit* attempter) {
	// Tool: can be NULL, in the case we have an action that doesn't require a tool (PK Fire or something)
	// If we explicitly require no tool, we should fail if we get any item for obj as we do manual checks for NULL wherever we search
	// Returns: -1 = not a valid tool at all (can't grab with a sword / NULL tool), 0 = not possible right now (can't grab if already holding), 1 = possible (empty hand), 2 = possible w/ targets
	// TODO: possible + usable, but requires other parts we dont have (walking requires 2 legs, but one leg is a valid tool)
	// TODO: enum for the reason why we cant: broken, no targets, need additional tools, not in range, etc

	std::cout << "Action " << actionName << " didn't make its own canUse?";
	World::me->pause();
	return -1;
}

std::vector<Item*> Action::getTools(Unit* attempter, int possibleLevel) {
	// possibleLevel: -1 = not valid at all (can't grab with a sword / NULL tool), 0 = possible but not usable (can't grab if already holding), 1 = possible (empty hand), 2 = possible w/ targets
	// Returns: All possible tools this action could use, including null if we don't NEED a tool

	std::cout << "Action " << actionName << " didn't make its own getTools?";
	World::me->pause();
	std::vector<Item*> failure;
	return failure;
}

std::vector<Item*> Action::getITargets(Item* tool, Unit* attempter) {
	std::cout << "Action " << actionName << " didn't make its own getITargets?";
	World::me->pause();
	std::vector<Item*> failure;
	return failure;
}

std::vector<Unit*> Action::getUTargets(Item* tool, Unit* attempter) {
	std::cout << "Action " << actionName << " didn't make its own getUTargets?";
	World::me->pause();
	std::vector<Unit*> failure;
	return failure;
}

std::vector<Entity*> Action::getETargets(Item* tool, Unit* attempter) {
	std::cout << "Action " << actionName << " didn't make its own getETargets?";
	World::me->pause();
	std::vector<Entity*> failure;
	return failure;

}

std::vector<Square*> Action::getSTargets(Item* tool, Unit* attempter) {
	std::cout << "Action " << actionName << " didn't make its own getSTargets?";
	World::me->pause();
	std::vector<Square*> failure;
	return failure;
}


int Action::getValue(Item* tool, Unit* attempter) {
	// Return whatever value this action is worth, assuming the tool is valid and possible to use already

//	std::cout << "Action " << actionName << " didn't make its own getValue?";
//	World::me->pause();
	return 1;
}


bool Action::canAttempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget) {
	if(howPossible(tool, attempter)<2) // TODO: inefficient, could probably do with just 1 or we search for targets x many times in a row
	{
		return false;
	}

	if(uTarget!=NULL)
	{
		bool result=World::me->vectorHas<Unit>(getUTargets(tool, attempter), uTarget);
		return result;
	}
	else if(iTarget!=NULL)
	{
		return World::me->vectorHas<Item>(getITargets(tool, attempter), iTarget);
	}
	else if(sTarget!=NULL)
	{
		return World::me->vectorHas<Square>(getSTargets(tool, attempter), sTarget);
	}
	else
	{
		std::cout << "Action " << actionName << " was given a weird canAttempt?";
		World::me->pause();
	}

	return true;
}

bool Action::couldAttempt(Item* tool, Unit* attempter, Square* fakeStart, Square* fakeEnd, bool risky) {
	std::cout << "Action " << actionName << " didn't make a square canAttempt?";
	World::me->pause();
	return false;
}


bool Action::tryAttempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget) {
	// This and attempt does not handle energy changes, should be done in actool
	// Returns true if we succeeded / failed / did something worth setting energy, false if we didn't do anything

	if(!canAttempt(tool, attempter, uTarget, iTarget, sTarget))
	{
		return false;
	}

	return attempt(tool, attempter, uTarget, iTarget, sTarget);
}

bool Action::attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget) {
	// The tool will always be usable: we tested in tryAttempt which is what should always be called first
	// Returns true if we succeeded / failed / did something worth setting energy, false if we didn't do anything

	std::cout << "Action " << actionName << " didn't make its own attempt?";
	World::me->pause();
	return false;
}


int Action::setEnergy(Unit* attempter, bool starting) {
	// TODO: complicated energy adjustment here, energyUse * energymod or something

	if(attempter!=NULL)
	{
		attempter->energy=starting ? castpoint : backswing;
	}

	return starting ? castpoint : backswing;
}

