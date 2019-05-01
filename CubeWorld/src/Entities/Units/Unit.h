
#ifndef UNIT_H_
#define UNIT_H_

#include "../Items/Item.h"
//#include "../Commands/Command.h"
#include "../Entity.h"
#include "../../Actions/Action.h"
#include "../../Tasks/Task.h"

#include <string>
#include <vector>

class Square;

class Unit : public Entity {
public:
	Unit(int x, int y, int z);
	virtual ~Unit();

//	std::string team;
	Item* brain;
	int staggerHp;
	int painHp;
	int soulHp;
	std::set<Item*> parts;

	Actool* activeActool;
	Unit* activeUTarget;
	Item* activeITarget;
	Square* activeSTarget;

	void update();
	void work();

	int canWalk(Square* here, Square* there);
	int canRiskwalk(Square* here, Square* there);
	int canFly(Square* here, Square* there);
	int canFall(Square* here, Square* there);
	int canMove(Square* here, Square* there);
	int canMove(Square* here, Square* there, Unit* ignore);
	int canPlanMove(Square* here, Square* there);
	int canPlanMove(Square* here, Square* there, Unit* ignore);
	bool tryPath(int x, int y, int z, bool risky, int howClose);
	int tryMove(int x, int y, int z, Entity* target);
	int tryMove(int x, int y, int z, Entity* target, bool actionMove, Actool* moveActool, Unit* exception);
	bool letMove(int x, int y, int z, Unit* exception);
	bool canDragMove(Unit* exception, bool attempting);
	virtual void moved(int x, int y, int z, int oldX, int oldY, int oldZ);

	void damage(int impactHit, int slashHit, int stabHit, int brokeHit,  int maxHit, int soulHit, Entity* cause, Entity* source, bool canEmbed);
	void damage(int impactHit, int slashHit, int stabHit, int brokeHit, int maxHit, int soulHit, Entity* cause, Entity* source, bool canEmbed, Item* target);
	int totalWeight();

	bool connected(Item* obj, int attachlevel, int storedLevel, int holdingLevel, int embedLevel);
	void attach(Item* obj, bool isBrain);
	void detach(Item* obj, bool refreshNow);
	void sever(Item* obj, bool refreshNow);
	void tryClaim(Item* obj, bool refreshNow);
	void drop(Item* obj, bool refreshNow);
	void dropped(Unit* dropper, bool refreshNow);
	void dead(Item* obj);

	std::vector<Item*> getBlob(bool includeBody, int storedLevel, int holdingLevel, int embedLevel, Unit* compareGuy, int ownerLevel, int activeLevel);
	std::vector<Unit*> connectedUnits();
	// attackable blob from items, then put it in world::get nearby items
	std::vector<Living*> refreshBlob();

	int count(std::string name, ItemTag tagType, bool includeBody, int storedLevel, int holdingLevel, int embedLevel, Unit* compareGuy, int ownerLevel, int activeLevel);
	Item* getPart(std::string name, ItemTag tagType, bool includeBody, int storedLevel, int holdingLevel, int embedLevel, Unit* compareGuy, int ownerLevel, int activeLevel);
	std::vector<Item*> getParts(std::string name, ItemTag tagType, bool includeBody, int storedLevel, int holdingLevel, int embedLevel, Unit* compareGuy, int ownerLevel, int activeLevel);

	Actool* getActool(std::string name, ActionTag type, ActionSubtag subType, int possibleLevel);
	Actool* getActool(std::string name, ActionTag type, ActionSubtag subType, Unit* uTarget, Item* iTarget, Square* sTarget);
	std::vector<Actool*> getActools(std::string name, ActionTag type, ActionSubtag subType, int possibleLevel);
	Action* getAction(std::string name, ActionTag type, ActionSubtag subType, int possibleLevel);
	std::vector<Action*> getActions(std::string name, ActionTag type, ActionSubtag subType, int possibleLevel);
	Task* getTask(std::string name);
	std::vector<Task*> getTasks(std::string name);

	void interrupt(int severity);
	void fullRefresh();
	bool refresh();
	void retag(std::multiset<Tag>* sharedTags);

	void tryDie();

	std::string name(int detail);
};

#endif /* UNIT_H_ */
