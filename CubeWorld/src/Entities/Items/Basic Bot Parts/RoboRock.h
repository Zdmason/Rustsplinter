
#ifndef ENTITIES_ITEMS_BASIC_BOT_PARTS_ROBOROCK_H_
#define ENTITIES_ITEMS_BASIC_BOT_PARTS_ROBOROCK_H_

#include "../Item.h"

class RoboRock : public Item {
public:
	RoboRock(int x, int y, int z);
	//~RoboRock();

	void print();
};

#endif /* ENTITIES_ITEMS_BASIC_BOT_PARTS_ROBOROCK_H_ */
