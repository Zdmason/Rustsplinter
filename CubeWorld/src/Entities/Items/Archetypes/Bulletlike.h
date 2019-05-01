
#ifndef ENTITIES_ITEMS_ARCHETYPES_BULLETLIKE_H_
#define ENTITIES_ITEMS_ARCHETYPES_BULLETLIKE_H_

#include "../Item.h"

class Bulletlike : public Item {
public:
	Bulletlike(int x, int y, int z);
	//~Bulletlike();

	int shootDamage;
//	void handleShot(Entity* target, int gunDamage);
};

#endif /* ENTITIES_ITEMS_ARCHETYPES_BULLETLIKE_H_ */
