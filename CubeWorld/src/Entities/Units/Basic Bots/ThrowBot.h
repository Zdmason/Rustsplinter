
#ifndef ENTITIES_UNITS_BASIC_BOTS_THROWBOT_H_
#define ENTITIES_UNITS_BASIC_BOTS_THROWBOT_H_

#include "../Unit.h"

class ThrowBot : public Unit {
public:
	ThrowBot(int x, int y, int z);
	//~ThrowBot();

	void print();
};

#endif /* ENTITIES_UNITS_BASIC_BOTS_THROWBOT_H_ */
