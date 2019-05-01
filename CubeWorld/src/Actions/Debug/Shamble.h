
#ifndef SHAMBLE_H_
#define SHAMBLE_H_

#include "../Archetypes/MeleeMovement.h"

class Shamble : public MeleeMovement {
public:
	Shamble();
	//~Shamble();

	int howPossible(Item* tool, Unit* attempter);

	std::vector<Item*> getTools(Unit* attempter, int possibleLevel);
};

#endif /* SHAMBLE_H_ */
