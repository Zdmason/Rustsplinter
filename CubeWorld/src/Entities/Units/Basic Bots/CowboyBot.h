
#ifndef ENTITIES_UNITS_BASIC_BOTS_COWBOYBOT_H_
#define ENTITIES_UNITS_BASIC_BOTS_COWBOYBOT_H_

#include "../Unit.h"

class CowboyBot : public Unit {
public:
	CowboyBot(int x, int y, int z);
	//~CowboyBot();

	void print();
};

#endif /* ENTITIES_UNITS_BASIC_BOTS_COWBOYBOT_H_ */
