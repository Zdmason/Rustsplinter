
#ifndef ENTITIES_UNITS_BASIC_BOTS_STABBERBOT_H_
#define ENTITIES_UNITS_BASIC_BOTS_STABBERBOT_H_

#include "../Unit.h"

class StabberBot : public Unit {
public:
	StabberBot(int x, int y, int z);
	//~StabberBot();

	void print();
};

#endif /* ENTITIES_UNITS_BASIC_BOTS_STABBERBOT_H_ */
