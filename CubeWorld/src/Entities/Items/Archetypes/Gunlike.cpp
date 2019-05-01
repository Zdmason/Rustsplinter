
#include "Gunlike.h"

#include "../../../Actions/Debug/Shoot.h"
//#include "../../../Actions/Debug/Reload.h"

#include <iostream>

Gunlike::Gunlike(int x, int y, int z) : Item(x, y, z) {
	species="Gunlike";

	selfTags.insert(GUNLIKE);

	shootDamage=50;

	selfActions.push_back(new Shoot());
//	selfActions.push_back(new Reload());
};
