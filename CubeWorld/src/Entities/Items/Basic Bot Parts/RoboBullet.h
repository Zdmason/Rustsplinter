
#ifndef ENTITIES_ITEMS_BASIC_BOT_PARTS_ROBOBULLET_H_
#define ENTITIES_ITEMS_BASIC_BOT_PARTS_ROBOBULLET_H_

#include "../Archetypes/Bulletlike.h"

class RoboBullet : public Bulletlike {
public:
	RoboBullet(int x, int y, int z);
	//~RoboBullet();

	void print();
};

#endif /* ENTITIES_ITEMS_BASIC_BOT_PARTS_ROBOBULLET_H_ */
