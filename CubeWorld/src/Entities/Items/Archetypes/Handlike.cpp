
#include "Handlike.h"

#include "../../../Actions/Debug/Grab.h"
#include "../../../Actions/Debug/Drop.h"
#include "../../../Actions/Debug/Store.h"
#include "../../../Actions/Debug/Crawl.h"

#include <iostream>

Handlike::Handlike(int x, int y, int z) : Item(x, y, z) {
	species="Handlike";

	selfTags.insert(HANDLIKE);

	selfActions.push_back(new Grab());
	selfActions.push_back(new Drop());
	selfActions.push_back(new Store());
	selfActions.push_back(new Crawl());
};
