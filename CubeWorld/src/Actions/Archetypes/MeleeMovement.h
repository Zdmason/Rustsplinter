
#ifndef ACTIONS_ARCHETYPES_MELEEMOVEMENT_H_
#define ACTIONS_ARCHETYPES_MELEEMOVEMENT_H_

#include "Movement.h"

class MeleeMovement : public Movement {
public:
	MeleeMovement();
	//~MeleeMovement();

	int howPossible(Item* tool, Unit* attempter);

	std::vector<Item*> getTools(Unit* attempter, int possibleLevel);
	std::vector<Square*> getSTargets(Item* tool, Unit* attempter);

	bool couldAttempt(Item* tool, Unit* attempter, Square* fakeStart, Square* fakeEnd, bool risky);

	bool attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget);
};

#endif /* ACTIONS_ARCHETYPES_MELEEMOVEMENT_H_ */
