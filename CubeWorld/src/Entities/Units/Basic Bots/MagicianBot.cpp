
#include "MagicianBot.h"
#include "../../../World.h"

#include "../../Items/Basic Bot Parts/WalkerBall.h"
#include "../../Items/Basic Bot Parts/RoboArm.h"

//#include "../../../Stati/Physical/Levitation.h"
#include "../../../Actions/Debug/CastLevitation.h"
#include "../../../Tasks/Debug/SpamLevitation.h"
#include "../../../Tasks/Debug/Wander.h"

#include <vector>

MagicianBot::MagicianBot(int x, int y, int z) : Unit(x, y, z) {
	species="MagicianBot";
	isAlive=true;

	addedActions.push_back(new CastLevitation());
	addedTasks.push_back(new SpamLevitation());
	addedTasks.push_back(new Wander());

	Item* myBody=new WalkerBall(xPos, yPos, zPos);
	World::me->addItem(myBody, this, NULL, BRAIN);

	World::me->addItem(new RoboArm(xPos, yPos, zPos), this, myBody, ORGAN);
}

void MagicianBot::print() {
	std::cout << "M";
}
