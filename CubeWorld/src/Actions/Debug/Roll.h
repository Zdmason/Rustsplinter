
#ifndef ROLL_H_
#define ROLL_H_

#include "../Archetypes/MeleeMovement.h"

class Roll : public MeleeMovement {
public:
	Roll();
	//~Roll();

	int howPossible(Item* tool, Unit* attempter);

	std::vector<Item*> getTools(Unit* attempter, int possibleLevel);
	std::vector<Square*> getSTargets(Item* tool, Unit* attempter);

	bool couldAttempt(Item* tool, Unit* attempter, Square* fakeStart, Square* fakeEnd, bool risky);
};

#endif /* ROLL_H_ */
