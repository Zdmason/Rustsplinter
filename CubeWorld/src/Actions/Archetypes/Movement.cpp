
#include "Movement.h"
#include "../../World.h"

Movement::Movement() : Action() {
	actionName="Movement";
	actionType=MOVEMENT;
}


int Movement::getValue(Item* tool, Unit* attempter) {
	if(castpoint+backswing<=0)
	{
		std::cout << "ERROR: movement action  " << actionName << " has speed below 0? ";
		World::me->pause();
		return 999;
	}

	// Lower speeds = low cooldown for walking = more valuable, so low speed = high value
	// 500 = 2000, 1000 = 1000, 1500=666, etc.
//	return 1000000.0/speed;

	// but above is with doubles and would be glitchy, so this works still
	return 10000-setEnergy(NULL, true)-setEnergy(NULL, false);
}
