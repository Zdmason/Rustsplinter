
#ifndef ENTITIES_ITEMS_BASIC_BOT_PARTS_ROBOGUN_H_
#define ENTITIES_ITEMS_BASIC_BOT_PARTS_ROBOGUN_H_

#include "../Archetypes/Gunlike.h"

class RoboGun : public Gunlike {
public:
	RoboGun(int x, int y, int z);
	//~RoboGun();

	void print();
};

#endif /* ENTITIES_ITEMS_BASIC_BOT_PARTS_ROBOGUN_H_ */
