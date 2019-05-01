
#ifndef ENTITIES_ITEMS_ARCHETYPES_GUNLIKE_H_
#define ENTITIES_ITEMS_ARCHETYPES_GUNLIKE_H_

#include "../Item.h"

class Gunlike : public Item {
public:
	Gunlike(int x, int y, int z);
	//~Gunlike();

	int shootDamage;
};

#endif /* ENTITIES_ITEMS_ARCHETYPES_GUNLIKE_H_ */
