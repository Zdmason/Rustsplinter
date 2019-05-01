
#ifndef DROP_H_
#define DROP_H_

#include "../Action.h"

class Drop : public Action {
public:
	Drop();
	//~Drop();

	int howPossible(Item* tool, Unit* attempter);

	std::vector<Item*> getTools(Unit* attempter, int possibleLevel);
	std::vector<Item*> getITargets(Item* tool, Unit* attempter);

	bool attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget);
};

#endif /* DROP_H_ */
