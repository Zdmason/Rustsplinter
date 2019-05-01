
#include "CanDo.h"

#include "../../World.h"

CanDo::CanDo() : Action() {
	actionName="CanDo";
	actionType=NULL_ACTION_TAG;
}


int CanDo::howPossible(Item* tool, Unit* attempter) {
	return 2;
}


std::vector<Item*> CanDo::getTools(Unit* attempter, int possibleLevel) {
	std::vector<Item*> nullVec;
	nullVec.push_back(NULL);
	return nullVec;
}


bool CanDo::attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget) {
	std::cout << "CANDO Actionede!!! ";

	return true;
}
