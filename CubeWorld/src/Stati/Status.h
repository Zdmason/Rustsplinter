
#ifndef STATUS_H_
#define STATUS_H_

#include "../Living.h"
#include "../Enums.h"

#include <vector>

class Entity;

class Status : public Living {
public:
	Status();
	virtual ~Status();

	std::vector<Tag> soloTags;
	std::vector<Tag> duoTags;
	int duration;
	int priority;
	Entity* victim; //TODO: change this to be like gravity and take in a lot of victims
	bool encompassing;

	virtual void copy(Entity* newVictim);

	virtual void update();
	virtual void work();
	virtual void subwork();

	virtual bool letInfect(Status* effect);
	virtual void onInfect();
	virtual void blocked();

	void fullRefresh();
	virtual bool refresh();
	virtual void dispell();
	virtual void expire();
	virtual void dead(Entity* thing);
	void disown(Entity* thing);
	virtual void onDie();

	virtual bool letDie(Entity* thing);
};

#endif /* STATUS_H_ */
