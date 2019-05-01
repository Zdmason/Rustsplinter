
#ifndef ACTIONS_ARCHETYPES_MOVEMENT_H_
#define ACTIONS_ARCHETYPES_MOVEMENT_H_

#include "../Action.h"

class Movement : public Action {
public:
	Movement();
	//~Movement();

//	int howPossible(Item* tool, Unit* attempter);

//	std::vector<Item*> getTools(Unit* attempter, int possibleLevel);
//	std::vector<Square*> getSTargets(Item* tool, Unit* attempter);

//	bool couldAttempt(Item* tool, Unit* attempter, Square* fakeStart, Square* fakeEnd, bool risky);

	int getValue(Item* tool, Unit* attempter);

//	int attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget);
};

#endif /* ACTIONS_ARCHETYPES_MOVEMENT_H_ */
