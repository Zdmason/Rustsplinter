
#ifndef FROGLEAP_H_
#define FROGLEAP_H_

#include "../Action.h"

class FrogLeap : public Action {
public:
	FrogLeap();
	//~FrogLeap();

	int howPossible(Item* tool, Unit* attempter);

	std::vector<Item*> getTools(Unit* attempter, int possibleLevel);
	std::vector<Square*> getSTargets(Item* tool, Unit* attempter);

	bool attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget);
};

#endif /* FROGLEAP_H_ */
