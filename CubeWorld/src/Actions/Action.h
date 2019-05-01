
#ifndef ACTION_H_
#define ACTION_H_

#include "../Entities/Entity.h"

#include <iostream>

class Unit;
class Item;
class Actool;

class Action {
public:
	Action();
	virtual ~Action();
	virtual void cloneTo(Item* obj, Unit* guy, bool selfOnly);

	int id;
//	double speedMod;
//	int cooldown;
//	int interruptCancle; // Minimum interrupt level before we stop whatever we were doing
	int castpoint; // Delay before attempting
	int backswing; // Delay after attempting

	std::string actionName;
	ActionTag actionType;
	ActionSubtag actionSubtype;

	// only used by specific tool: melee attack, grab
	//		Item's selfActions only
	// possibly both: roundhouse kick, throat punch, improvements to normal hits, etc
	//		selfAction or addedActions
	// Only to be used generally: magic spells, I CAST FIST
	//		addedActions only
	// CAN be cast with NULL, but can also use a tool to do things more effectively: wizard lighting / wizard lightning with a staff
	//		addedActions only


	Actool* getActool(Item* tool, Unit* attempter, int possibleLevel); // Don't change these, they're based off checking the below automatically
	std::vector<Actool*> getActools(Unit* attempter, int possibleLevel);

	virtual int howPossible(Item* tool, Unit* attempter); 						// Change this for all actions
	virtual std::vector<Item*> getTools(Unit* attempter, int possibleLevel);	// Change this for all actions
	virtual std::vector<Item*> getITargets(Item* tool, Unit* attempter);
	virtual std::vector<Unit*> getUTargets(Item* tool, Unit* attempter);	// Change these only if its relevant for the action
	virtual std::vector<Entity*> getETargets(Item* tool, Unit* attempter);
	virtual std::vector<Square*> getSTargets(Item* tool, Unit* attempter);
	// TODO: 'smart' bool for above, when you really only want to target enemies with attacks / grabs / whatever / only target nonrisky movement options

	virtual int getValue(Item* tool, Unit* attempter); // Change this for actions where it doesn't matter if the value is different than 1 (AKA: all grabbing is the same, but melee attacks can do different damages)

	bool canAttempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget);
	virtual bool couldAttempt(Item* tool, Unit* attempter, Square* fakeStart, Square* fakeEnd, bool risky); // Change this only for movement based actions

	bool tryAttempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget);
	virtual bool attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget); // Change this for all actions

	int setEnergy(Unit* attempter, bool starting);
};

#endif /* ACTION_H_ */
