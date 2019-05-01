
#ifndef DEBUGKARATE_H_
#define DEBUGKARATE_H_

#include "../Action.h"

class DebugKarate : public Action {
public:
	DebugKarate();
	//~DebugKarate();

	int howPossible(Item* tool, Unit* attempter);

	std::vector<Item*> getTools(Unit* attempter, int possibleLevel);
	std::vector<Unit*> getUTargets(Item* tool, Unit* attempter);

	bool attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget);
};

#endif /* DEBUGKARATE_H_ */
