
#ifndef ENTITIES_ITEMS_BASIC_BOT_PARTS_ROBOPACK_H_
#define ENTITIES_ITEMS_BASIC_BOT_PARTS_ROBOPACK_H_

#include "../Item.h"

class RoboPack : public Item {
public:
	RoboPack(int x, int y, int z);
	//~RoboPack();

	void print();
};

#endif /* ENTITIES_ITEMS_BASIC_BOT_PARTS_ROBOPACK_H_ */
