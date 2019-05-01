
#ifndef ENTITIES_UNITS_BASIC_BOTS_ARMORBOT_H_
#define ENTITIES_UNITS_BASIC_BOTS_ARMORBOT_H_

#include "../Unit.h"

class ArmorBot : public Unit {
public:
	ArmorBot(int x, int y, int z);
	//~ArmorBot();

	void print();
};

#endif /* ENTITIES_UNITS_BASIC_BOTS_ARMORBOT_H_ */
