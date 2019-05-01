
#ifndef ACTIONS_ATTACKS_MAKESHIFTATTACK_H_
#define ACTIONS_ATTACKS_MAKESHIFTATTACK_H_

#include "../Action.h"

class MakeshiftAttack : public Action {
public:
	MakeshiftAttack();
	//~MakeshiftAttack();

	int howPossible(Item* tool, Unit* attempter);

	std::vector<Item*> getTools(Unit* attempter, int possibleLevel);
	std::vector<Item*> getITargets(Item* tool, Unit* attempter);
	std::vector<Unit*> getUTargets(Item* tool, Unit* attempter);

	int getValue(Item* tool, Unit* attempter);

	bool attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget);
};

#endif /* ACTIONS_ATTACKS_MAKESHIFTATTACK_H_ */
