
#ifndef WORLD_H_
#define WORLD_H_

#include "Square.h"
#include "LivingQueue.h"
#include "Entities/Blocks/Block.h"
#include "Physics/Gravity.h"
#include "Actions/Actool.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>


class World {
public:
	World(int x, int y, int z, std::string* preset, int delay, int totalLanes);
	//~World();

	static World* me;

	int xMax, yMax, zMax;
	Square**** cube;

	int delay;
	int numLanes;
	int curId;

	static int forcePerDamage; // Force = velocity * weight, damage = force / this. Use this so you can change this universally across all physics-related damage
	static int curPath;
	static int curTick;

	std::list<Unit*> units;
	std::list<Item*> items;
	std::map<int, Entity*> entities;
	std::list<Status*> stati;
	static std::list<Living*> activeThings;
	static LivingQueue activeQueue;
	std::queue<Living*> refreshQueue;

	Entity* getEntId(int targetId);
	void addRefresher(Living* thing, bool refreshNow);
	void handleRefresh();

	void addBlock(Block* block);
	void moveBlock(Block* block, int x, int y, int z);
	void remBlock(Block* block);

	void addUnit(Unit* guy);
	void moveUnit(Unit* guy, int x, int y, int z);
	void remUnit(Unit* guy);

	Item* addItem(Item* obj, Unit* guy, Item* thing, ItemCarryStatus initStatus);
	void moveItem(Item* obj, int x, int y, int z);
	void submoveItem(Item* obj, int x, int y, int z);
	void hideItem(Item* obj, Entity* hider);
	void unhideItem(Item* obj);
	void remItem(Item* obj);

	int tryMoveThing(int x, int y, int z, Entity* thing, bool actMove);
	void moveThing(int x, int y, int z, Entity* thing);

	void addStatus(Status* effect, Entity* victim, bool copying);
	void remStatus(Status* effect);

	void addGravity(Gravity* momentum);
	void remGravity(Gravity* momentum);


	std::queue<Square*> getNear(int x, int y, int z);
	std::vector<Square*> getNearbySquares(int x, int y, int z, double radius, bool onlyTargetable);
	std::vector<Unit*> getNearbyUnits(int x, int y, int z, double radius, bool onlyTargetable);
	std::vector<Item*> getNearbyItems(int x, int y, int z, double radius, bool onlyTargetable, int includeUnitParts, Unit* ignoreMe);

	double distance(int hereX, int hereY, int hereZ, int thereX, int thereY, int thereZ);
	double heuristic(int hereX, int hereY, int hereZ, int thereX, int thereY, int thereZ);
	int gcd(int a, int b);
	int lcm(int a, int b);
	int random(int min, int max);

	template <class T>
	bool vectorHas(std::vector<T*> vec, T* thing) {
		for(unsigned int i=0;i<vec.size();i++)
		{
			if(vec[i]==thing)
			{
				return true;
			}
		}
		return false;
	}

	bool canSeeTo(int x, int y, int z, int xx, int yy, int zz, bool inner, int howClose);
	Entity* tryTargetTo(int x, int y, int z, int xx, int yy, int zz, bool inner, int howClose);
	Entity* intRaycastHit(int x, int xAdd, int y, int yAdd, int z, int zAdd, int xx, int xxAdd, int yy, int yyAdd, int zz, int zzAdd, int howClose);
	std::queue<Square*> tryRaypathTo(int x, int y, int z, int xx, int yy, int zz, bool inner, int howClose);
	std::queue<Square*> intRaycastPath(int x, int xAdd, int y, int yAdd, int z, int zAdd, int xx, int xxAdd, int yy, int yyAdd, int zz, int zzAdd, int howClose);

	// pathRayTo: returns a path to the target excluding the target square, or returns a single square to -666 if something interrupted the raycast

	/*
	void glance(Unit* seer);
	void unglance(Unit* unseer);
	void castLight(int x, int y, int radius, int row, float startSlope, float endSlope, int xx, int xy, int yx, int yy, Unit* seer);
	std::multiset<Square*> getTargetable(Unit* seeker);
	std::vector<Square*> castAim(int x, int y, int row, float startSlope, float endSlope, int xx, int xy, int yx, int yy);


	// FindClose-x: breadth first search for visible thing that matches the qualifications. If invis, use getAll + filter

	Unit* findCloseUnit(Unit* seeker);
	Unit* findCloseUnitSpecies(Unit* seeker, std::string targetSpec);
	Unit* findCloseUnitTag(Unit* seeker, Tag targetTag);
	Unit* findCloseAlly(Unit* seeker);
	Unit* findCloseAllySpecies(Unit* seeker, std::string targetSpec);
	Unit* findCloseAllyTag(Unit* seeker, Tag targetTag);
	Unit* findCloseEnemy(Unit* seeker);
	Unit* findCloseEnemySpecies(Unit* seeker, std::string targetSpec);
	Unit* findCloseEnemyTag(Unit* seeker, Tag targetTag);
	Item* findCloseFreeItem(Unit* seeker);
	Item* findCloseFreeItemSpecies(Unit* seeker, std::string targetSpec);
	Item* findCloseFreeItemTag(Unit* seeker, Tag targetTag);
	Item* findCloseOwnedItem(Unit* seeker);
	Item* findCloseOwnedItemSpecies(Unit* seeker, std::string targetSpec);
	Item* findCloseOwnedItemTag(Unit* seeker, Tag targetTag);

	// TargetClose-x: breadth first search for visible thing that matches the qualifications and can be rayed to by the seeker.

	Unit* targetCloseUnit(Unit* seeker);
	Unit* targetCloseUnitSpecies(Unit* seeker, std::string targetSpec);
	Unit* targetCloseUnitTag(Unit* seeker, Tag targetTag);
	Unit* targetCloseAlly(Unit* seeker);
	Unit* targetCloseAllySpecies(Unit* seeker, std::string targetSpec);
	Unit* targetCloseAllyTag(Unit* seeker, Tag targetTag);
	Unit* targetCloseEnemy(Unit* seeker);
	Unit* targetCloseEnemySpecies(Unit* seeker, std::string targetSpec);
	Unit* targetCloseEnemyTag(Unit* seeker, Tag targetTag);

	// getAll-x: returns all things within a given radius, depending on whats given.

	std::vector<Unit*> getAllBasic(Unit* seeker);
	std::vector<Unit*> getAllUnit(int radius, int xx, int yy);
	std::vector<Unit*> getAllUnit(Unit* seeker);
	std::vector<Unit*> getAllNeutral(int radius, int xx, int yy);
	std::vector<Unit*> getAllNeutral(Unit* seeker);
	std::vector<Unit*> getAllAlly(int radius, int xx, int yy, std::string myTeam);
	std::vector<Unit*> getAllAlly(Unit* seeker);
	std::vector<Unit*> getAllEnemy(int radius, int xx, int yy, std::string myTeam);
	std::vector<Unit*> getAllEnemy(Unit* seeker);
	std::vector<Item*> getAllFreeItem(int radius, int xx, int yy);
	std::vector<Item*> getAllFreeItem(Unit* seeker);
	std::vector<Item*> getAllOwnedItem(int radius, int xx, int yy);
	std::vector<Item*> getAllOwnedItem(Unit* seeker);

	// filter-x: filters a vector for specific qualities

	std::vector<Unit*> filterSpecies(std::vector<Unit*> uList, std::string spec);
	std::vector<Item*> filterSpecies(std::vector<Item*> iList, std::string spec);
	std::vector<Unit*> filterVisible(std::vector<Unit*> uList, bool onlyVis);
	std::vector<Item*> filterVisible(std::vector<Item*> iList, bool onlyVis);
	std::vector<Unit*> filterCircle(std::vector<Unit*> uList, int radius, int xx, int yy);
	std::vector<Item*> filterCircle(std::vector<Item*> iList, int radius, int xx, int yy);
	std::vector<Unit*> filterTeam(std::vector<Unit*> uList, std::string myTeam, bool keep);
	std::vector<Item*> filterTeam(std::vector<Item*> iList, std::string myTeam, bool keep);
	std::vector<Unit*> filterTag(std::vector<Unit*> uList, Tag targetTag, bool keep);
	std::vector<Item*> filterTag(std::vector<Item*> iList, Tag targetTag, bool keep);
	std::vector<Unit*> filterSeeable(std::vector<Unit*> uList, Unit* seeker);
	std::vector<Item*> filterSeeable(std::vector<Item*> iList, Unit* seeker);
	std::vector<Unit*> filterTargetable(std::vector<Unit*> uList, Unit* seeker);
	std::vector<Item*> filterTargetable(std::vector<Item*> iList, Unit* seeker);
	std::vector<Unit*> filterHolding(std::vector<Unit*> uList, bool onlyHolders);
	std::vector<Item*> filterHolding(std::vector<Item*> iList, bool onlyHeld);
*/
	// Pathing using A* and the seeker's version of canMove


	Square* starPath(Unit* seeker, int targetX, int targetY, int targetZ, std::vector<Actool*> movements, bool risky, int howClose);

//	std::queue<Square*> pathTo(Unit* seeker, Unit* target);
//	std::queue<Square*> pathTo(Unit* seeker, int targetX, int targetY);
//	std::queue<Square*> pathTo(Unit* seeker, std::vector<Unit*> uList);
//	std::queue<Square*> pathTo(Unit* seeker, std::vector<Item*> iList);
//	std::queue<Square*> pathOn(Unit* seeker, Unit* target);
//	std::queue<Square*> pathOn(Unit* seeker, int targetX, int targetY);
//	std::queue<Square*> pathOn(Unit* seeker, std::vector<Unit*> uList);
//	std::queue<Square*> pathOn(Unit* seeker, std::vector<Item*> iList);

	Square* fearOne(Unit* runner, int targetX, int targetY);
	Square* fearAll(Unit* runner);

	void go();
	void stall();
	void pause();
	void print();
};

#endif /* WORLD_H_ */
