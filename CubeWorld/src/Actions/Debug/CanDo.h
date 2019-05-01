
#ifndef CANDO_H_
#define CANDO_H_

#include "../Action.h"

class CanDo : public Action {
public:
	CanDo();
	//~CanDo();

	int howPossible(Item* tool, Unit* attempter);

	std::vector<Item*> getTools(Unit* attempter, int possibleLevel);

	bool attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget);
};

#endif /* CANDO_H_ */
