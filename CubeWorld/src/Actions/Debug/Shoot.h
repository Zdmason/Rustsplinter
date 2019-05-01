
#ifndef ACTIONS_DEBUG_SHOOT_H_
#define ACTIONS_DEBUG_SHOOT_H_

#include "../Action.h"

class Shoot : public Action {
public:
	Shoot();
	//~Shoot();

	int howPossible(Item* tool, Unit* attempter);

	std::vector<Item*> getTools(Unit* attempter, int possibleLevel);
	std::vector<Item*> getITargets(Item* tool, Unit* attempter);
	std::vector<Unit*> getUTargets(Item* tool, Unit* attempter);
	std::vector<Square*> getSTargets(Item* tool, Unit* attempter);

	int getValue(Item* tool, Unit* attempter);

	bool attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget);
};

#endif /* ACTIONS_DEBUG_SHOOT_H_ */
