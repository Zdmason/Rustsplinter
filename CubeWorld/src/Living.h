
#ifndef LIVING_H_
#define LIVING_H_

#include "Enums.h"

#include <string>

class Living {
public:
	Living();
	virtual ~Living();

	Order order;
	std::string species;
	int id;

	bool isAlive;
	int initStatus; // 0 = initializing, 1 = alive, 2 = dead     TODO: these should be enums instead of ints
	int speed;
	int energy;

	//virtual void age(int time);
	virtual void update();
	virtual void work();

	virtual bool letMove(int x, int y, int z);

	virtual void fullRefresh();
	virtual bool refresh();

	virtual std::string name(int detail);
};

#endif /* LIVING_H_ */
