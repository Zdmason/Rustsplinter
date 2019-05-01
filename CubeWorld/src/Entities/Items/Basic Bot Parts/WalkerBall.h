
#ifndef WALKERBALL_H_
#define WALKERBALL_H_

#include "../Item.h"

class WalkerBall : public Item {
public:
	WalkerBall(int x, int y, int z);
	//~WalkerBall();

	void print();
};

#endif /* WALKERBALL_H_ */
