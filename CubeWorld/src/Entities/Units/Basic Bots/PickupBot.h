
#ifndef ENTITIES_UNITS_BASIC_BOTS_PICKUPBOT_H_
#define ENTITIES_UNITS_BASIC_BOTS_PICKUPBOT_H_

#include "../Unit.h"

class PickupBot : public Unit {
public:
	PickupBot(int x, int y, int z);
	//~PickupBot();

	void print();
};

#endif /* ENTITIES_UNITS_BASIC_BOTS_PICKUPBOT_H_ */
