
#include "../World.h"
#include "Actool.h"

Actool::Actool(Action* myAct, Item* obj, Unit* guy) {
	if(myAct==NULL)
	{
		std::cout << "ERROR: actool was given a null act wtf";
		World::me->pause();
	}

	// Actools can have null tools though, it shows we can perform the action without needing an item for it

	act=myAct;
	tool=obj;
	attempter=guy;


	// TODO: add this to world's list of things to delete every now and then
	// TODO: above = "garbage dump" vector of objects that should be deleted every update or so?
}

Actool::~Actool() {
//	; // TODO: make this / replace die()?
}


int Actool::howPossible() {
	return act->howPossible(tool, attempter);
}

std::vector<Item*> Actool::getITargets() {
	return act->getITargets(tool, attempter);
}

std::vector<Unit*> Actool::getUTargets() {
	return act->getUTargets(tool, attempter);
}

std::vector<Entity*> Actool::getETargets() {
	return act->getETargets(tool, attempter);
}

std::vector<Square*> Actool::getSTargets() {
	return act->getSTargets(tool, attempter);
}


int Actool::getValue() {
	return act->getValue(tool, attempter);
}


bool Actool::canAttempt(Unit* uTarget, Item* iTarget, Square* sTarget) {
	return act->canAttempt(tool, attempter, uTarget, iTarget, sTarget);
}

bool Actool::couldAttempt(Square* fakeStart, Square* fakeEnd, bool risky) {
	return act->couldAttempt(tool, attempter, fakeStart, fakeEnd, risky);
}


bool Actool::startAttempt(Unit* uTarget, Item* iTarget, Square* sTarget) {
	// Should be called by normal tasks, not anything from action

	if(!act->canAttempt(tool, attempter, uTarget, iTarget, sTarget))
	{
		return false;
	}

	if(act->castpoint==0) // If castpoint is 0 = instant activation, we can skip the wait and tryAttempt immidately
	{
		return tryAttempt(uTarget, iTarget, sTarget, true);
	}

	std::cout << " (started action " << act->actionName << "!) ";
	attempter->activeActool=this;
	attempter->activeITarget=iTarget;
	attempter->activeUTarget=uTarget;
	attempter->activeSTarget=sTarget;
	act->setEnergy(attempter, true);
	return true;
}

bool Actool::tryAttempt(Unit* uTarget, Item* iTarget, Square* sTarget, bool handleEnergy) {

	bool didAttempt=act->tryAttempt(tool, attempter, uTarget, iTarget, sTarget);

	if(didAttempt && handleEnergy)
	{
		act->setEnergy(attempter, false);
	}

	return didAttempt;
}
