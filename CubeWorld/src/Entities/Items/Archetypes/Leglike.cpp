
#include "Leglike.h"

#include "../../../Actions/Debug/Walk.h"

#include <iostream>

Leglike::Leglike(int x, int y, int z) : Item(x, y, z) {
	species="Leglike";

	selfTags.insert(LEGLIKE);

	selfActions.push_back(new Walk());
	// TODO: kicking? a leg can be a club like normal, or a force that does impact damage?
};
