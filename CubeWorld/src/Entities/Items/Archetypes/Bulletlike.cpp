
#include "Bulletlike.h"

#include <iostream>

Bulletlike::Bulletlike(int x, int y, int z) : Item(x, y, z) {
	species="Bulletlike";

	selfTags.insert(BULLETLIKE);

	shootDamage=50;
};
