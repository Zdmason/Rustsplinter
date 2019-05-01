
#ifndef FROGBOT_H_
#define FROGBOT_H_

#include "../Unit.h"

class FrogBot : public Unit {
public:
	FrogBot(int x, int y, int z);
	//~FrogBot();

	void print();
};

#endif /* FROGBOT_H_ */
