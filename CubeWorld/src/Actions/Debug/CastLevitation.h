
#ifndef CASTLEVITATION_H_
#define CASTLEVITATION_H_

#include "../Action.h"

class CastLevitation : public Action {
public:
	CastLevitation();
	//~CastLevitation();

	int howPossible(Item* tool, Unit* attempter);

	std::vector<Item*> getTools(Unit* attempter, int possibleLevel);
	std::vector<Item*> getITargets(Item* tool, Unit* attempter);
	std::vector<Unit*> getUTargets(Item* tool, Unit* attempter);

	bool attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget);
};

#endif /* CASTLEVITATION_H_ */
