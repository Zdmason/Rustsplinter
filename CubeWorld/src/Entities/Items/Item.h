
#ifndef ITEM_H_
#define ITEM_H_

#include "../Entity.h"

#include <list>

class Unit;

class Item : public Entity {
public:
	Item(int x, int y, int z);
	virtual ~Item();

	Unit* owner;
	int brokeHp;
	// int useless hp; TODO: piercing damage does this, 100 spear stabs sholdn't make a body explode from the inside? also bloodloss leads to this?
	int severHp;
	int maxHp;
	int maxMaxHp;

	int weight;

	int strength;

	std::vector<Action*> selfActions;

	std::set<Item*> attached;
	//std::set<Item*> semitached; TODO: for things like backpacks that arent armor but also arnt "organs"?
	//std::set<Item*> teletached; TODO: things we're connected to without directly touching, rare, will require special handling / refreshing, basically the same as now so delay use

	Item* holding;
	std::set<Item*> holders;
	Item* armor;
	std::set<Item*> storing;
	Item* storer;
	std::set<Item*> embedders;
	Item* embedding;
	std::multiset<ItemTag> selfTags; // Tags describing what this item is generally used for, mainly for giving it related default actions on startup
	std::multiset<Tag> organTags; // Tags only applied if this item is active and is someone's organ
	std::multiset<Tag> heldTags; // Tags only applied if this item is active and being held by someone

	void update();
	virtual void subwork();

	int canMove(Square* here, Square* there);
	int canPlanMove(Square* here, Square* there);
	int tryMove(int x, int y, int z, Entity* target);
	virtual void moved(int x, int y, int z, int oldX, int oldY, int oldZ);
	int throwAt(Entity* target, int x, int y, int z, int amount);

	void damage(int impactHit, int slashHit, int stabHit, int brokeHit, int maxHit, int soulHit, Entity* cause, Entity* villain, bool canEmbed);
	void damage(int impactHit, int slashHit, int stabHit, int brokeHit, int maxHit, int soulHit, Entity* cause, Entity* villain, bool canEmbed, bool armorCheck, Item* realTarget);

	std::vector<Unit*> bestOwners();
	int bestCarryLevel(Unit* checker);
	std::set<ItemCarryStatus> allCarryStati(Unit* checker);
	int strengthLevel(Unit* checker);
	int totalWeight();

	std::vector<Item*> getBlob(int attachLevel, int storedLevel, int holdingLevel, int embedLevel, Unit* guy, int ownerLevel, int activeLevel);
	std::vector<Item*> attackableBlob();
	std::vector<Living*> refreshBlob();
	bool connected(Item* obj, int attachLevel, int storedLevel, int holdingLevel, int embedLevel); // TODO: chain of being active / same type (bio, mechanical) for if heart reaches

	void attach(Item* obj, bool isBrain, bool refreshNow);
	void sever(Item* obj,  bool refreshNow);
	void disowned( bool refreshNow);
	void armortach(Item* obj,  bool refreshNow);
	void armorsever( bool refreshNow);
	void grab(Item* obj,  bool refreshNow);
	void drop( bool refreshNow);
	void fullDrop( bool refreshNow);
	void store(Item* obj, bool refreshNow);
	void unstore(Item* obj, bool refreshNow);
//	void storeInto(Item* obj);
	void embed(Item* obj, bool refreshNow);
	void dislodge(Item* obj, bool refreshNow);

	int count(std::string name, ItemTag tagType, int attachLevel, int storedLevel, int holdingLevel, int embedLevel, Unit* guy, int ownerLevel, int activeLevel);
	Item* getPart(std::string name, ItemTag tagType, int attachLevel, int storedLevel, int holdingLevel, int embedLevel, Unit* guy, int ownerLevel, int activeLevel);
	std::vector<Item*> getParts(std::string name, ItemTag tagType, int attachLevel, int storedLevel, int holdingLevel, int embedLevel, Unit* guy, int ownerLevel, int activeLevel);

	void fullRefresh();
	bool refresh();
	bool isActive();
	bool isUseable(Unit* user);
	bool isManipulatable(Unit* user);
	void retag(std::multiset<Tag>* sharedTags);

	void tryDie();

	std::string name(int detail);
};

#endif /* ITEM_H_ */
