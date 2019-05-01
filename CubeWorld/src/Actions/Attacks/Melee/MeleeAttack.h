
#ifndef ACTIONS_ATTACKS_MELEE_MELEEATTACK_H_
#define ACTIONS_ATTACKS_MELEE_MELEEATTACK_H_

#include "../../Action.h"

class MeleeAttack : public Action {
public:
	MeleeAttack(std::string myName, int myImpactScale, int mySlashScale, int mySlashMax, int myStabScale, int myStabMax, int myBrokeDamage, int myMaxDamage, int mySoulDamage);
	//~MeleeAttack();

	std::string name;
	// TODO: int impactAdd; for things like rocket-boosted hammer swings where its more than flat damage
	int impactScale; // Default is 1 str = 1000 impact scale, so something better like a hammer would be 2000 per or something
	int slashScale;
	int slashMax;
	int stabScale;
	int stabMax;
	int brokeDamage;
	int maxDamage;
	int soulDamage;

	int howPossible(Item* tool, Unit* attempter);

	std::vector<Item*> getTools(Unit* attempter, int possibleLevel);
	std::vector<Item*> getITargets(Item* tool, Unit* attempter);
	std::vector<Unit*> getUTargets(Item* tool, Unit* attempter);

	int getValue(Item* tool, Unit* attempter);

	bool attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget);
};

#endif /* ACTIONS_ATTACKS_MELEE_MELEEATTACK_H_ */
