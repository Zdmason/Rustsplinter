
#ifndef ACTIONS_ACTOOL_H_
#define ACTIONS_ACTOOL_H_

#include "Action.h"

class Actool {
public:
	Actool(Action* act, Item* obj, Unit* guy);
	~Actool();

	Action* act;
	Item* tool;
	Unit* attempter;

	int howPossible();

	std::vector<Item*> getITargets();
	std::vector<Unit*> getUTargets();
	std::vector<Entity*> getETargets();
	std::vector<Square*> getSTargets();
	// TODO: 'smart' bool for above, when you really only want to target enemies with attacks / grabs / whatever

	int getValue();

	bool canAttempt(Unit* uTarget, Item* iTarget, Square* sTarget);
	bool couldAttempt(Square* fakeStart, Square* fakeEnd, bool risky);

	bool startAttempt(Unit* uTarget, Item* iTarget, Square* sTarget);
	bool tryAttempt(Unit* uTarget, Item* iTarget, Square* sTarget, bool handleEnergy);
};

#endif /* ACTIONS_ACTOOL_H_ */
