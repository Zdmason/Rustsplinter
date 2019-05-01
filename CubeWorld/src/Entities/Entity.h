
#ifndef ENTITY_H_
#define ENTITY_H_

#include "../Living.h"
#include "../Stati/Status.h"

class Square;
class Gravity;
class Action;
class Task;

#include <set>
#include <list>
#include <vector>

class Entity : public Living {
public:
	Entity(int x, int y, int z);
	virtual ~Entity();

	int xPos, yPos, zPos;
	std::multiset<Tag> tags;
	std::multiset<Tag> soloTags;
	std::multiset<Tag> duoTags;

	std::vector<Action*> addedActions;
	std::vector<Task*> addedTasks;

	Gravity* myGrav;
	std::vector<Status*> stati;
	//bool visible;
	bool isHidden;
	bool worked;
	//int size;

	virtual int canMove(Square* here, Square* there);
	virtual int canPlanMove(Square* here, Square* there);
	virtual int canBlink(Square* here, Square* there);
	virtual int tryMove(int x, int y, int z, Entity* collideTarget);
	virtual void moved(int x, int y, int z, int oldX, int oldY, int oldZ);

	virtual bool letInfect(Status* effect);
	virtual bool letSelfInfect(Status* effect);
	virtual void damage(int impactHit, int slashHit, int stabHit, int brokeHit, int maxHit, int soulHit, Entity* cause, Entity* source, bool canEmbed);
	virtual int totalWeight();
	virtual void collide(Entity* victim, bool spread);
	virtual bool addGravForce(int xAmount, int yAmount, int zAmount, Entity* villain, Entity* target, bool overwrite);
	virtual bool addGravForce(int sourceX, int sourceY, int sourceZ, Entity* villain, Entity* target, int amount); // Putting amount in front = ambiguous errors if entities are null
	virtual bool addGravForce(int amount, Entity* thing, int targetLevel, Entity* villain);

	virtual std::vector<Living*> refreshBlob();
	virtual void retag(std::multiset<Tag>* sharedTags);
	virtual bool fallCheck();

	virtual void tryDie();
	virtual bool letDie(Entity* dier);
	virtual void onDie();

	virtual void print();
};

#endif /* ENTITY_H_ */
