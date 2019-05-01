
#ifndef ZOMBIEBOT_H_
#define ZOMBIEBOT_H_

#include "../Unit.h"

class ZombieBot : public Unit {
public:
	ZombieBot(int x, int y, int z);
	//~ZombieBot();

	void print();
};

#endif /* ZOMBIEBOT_H_ */
