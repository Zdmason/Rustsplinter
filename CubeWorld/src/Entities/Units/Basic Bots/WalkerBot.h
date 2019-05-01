
#ifndef WALKERBOT_H_
#define WALKERBOT_H_

#include "../Unit.h"

class WalkerBot : public Unit {
public:
	WalkerBot(int x, int y, int z);
	//~WalkerBot();

	void print();
};

#endif /* WALKERBOT_H_ */
