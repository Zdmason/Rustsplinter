
#ifndef GRAB_H_
#define GRAB_H_

#include "../Action.h"

class Grab : public Action {
public:
	Grab();
	//~Grab();

	int howPossible(Item* tool, Unit* attempter);

	std::vector<Item*> getTools(Unit* attempter, int possibleLevel);
	std::vector<Item*> getITargets(Item* tool, Unit* attempter);
	std::vector<Unit*> getUTargets(Item* tool, Unit* attempter);

	bool attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget);
};

#endif /* GRAB_H_ */
