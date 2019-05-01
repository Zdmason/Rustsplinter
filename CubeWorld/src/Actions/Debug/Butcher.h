
#ifndef ACTIONS_DEBUG_BUTCHER_H_
#define ACTIONS_DEBUG_BUTCHER_H_

#include "../Action.h"

class Butcher : public Action {
public:
	Butcher();
	//~Butcher();

	int howPossible(Item* tool, Unit* attempter);

	std::vector<Item*> getTools(Unit* attempter, int possibleLevel);
	std::vector<Item*> getITargets(Item* tool, Unit* attempter);

	bool attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget);
};

#endif /* ACTIONS_DEBUG_BUTCHER_H_ */
