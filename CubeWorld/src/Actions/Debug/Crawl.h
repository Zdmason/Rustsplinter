
#ifndef ACTIONS_DEBUG_CRAWL_H_
#define ACTIONS_DEBUG_CRAWL_H_

#include "../Archetypes/MeleeMovement.h"

class Crawl : public MeleeMovement {
public:
	Crawl();
	//~Crawl();

	int howPossible(Item* tool, Unit* attempter);

	std::vector<Item*> getTools(Unit* attempter, int possibleLevel);
};

#endif /* ACTIONS_DEBUG_CRAWL_H_ */
