
#include "CowboyBot.h"
#include "../../../World.h"

#include "../../Items/Basic Bot Parts/WalkerBall.h"
#include "../../Items/Basic Bot Parts/RoboArm.h"
#include "../../Items/Basic Bot Parts/RoboGun.h"
#include "../../Items/Basic Bot Parts/RoboBullet.h"

#include "../../../Tasks/Debug/SpamShoot.h"
#include "../../../Tasks/Debug/RiskWander.h"

#include <vector>

CowboyBot::CowboyBot(int x, int y, int z) : Unit(x, y, z) {
	species="CowboyBot";
	isAlive=true;

	soulHp=10;

	addedTasks.push_back(new SpamShoot());
	addedTasks.push_back(new RiskWander());

	Item* myBody=World::me->addItem(new WalkerBall(xPos, yPos, zPos), this, NULL, BRAIN);

	Item* myArm=World::me->addItem(new RoboArm(xPos, yPos, zPos), this, myBody, ORGAN);
	Item* myArmgun=World::me->addItem(new RoboGun(xPos, yPos, zPos), this, myArm, HELD);
	World::me->addItem(new RoboBullet(xPos, yPos, zPos), this, myArmgun, STORED);
	World::me->addItem(new RoboBullet(xPos, yPos, zPos), this, myArmgun, STORED);
	World::me->addItem(new RoboBullet(xPos, yPos, zPos), this, myArmgun, STORED);
	World::me->addItem(new RoboBullet(xPos, yPos, zPos), this, myArmgun, STORED);
	World::me->addItem(new RoboBullet(xPos, yPos, zPos), this, myArmgun, STORED);
	World::me->addItem(new RoboBullet(xPos, yPos, zPos), this, myArmgun, STORED);

	Item* myGunarm=World::me->addItem(new RoboGun(xPos, yPos, zPos), this, myBody, ORGAN);
	World::me->addItem(new RoboBullet(xPos, yPos, zPos), this, myGunarm, STORED);
	World::me->addItem(new RoboBullet(xPos, yPos, zPos), this, myGunarm, STORED);
	World::me->addItem(new RoboBullet(xPos, yPos, zPos), this, myGunarm, STORED);
	World::me->addItem(new RoboBullet(xPos, yPos, zPos), this, myGunarm, STORED);
	World::me->addItem(new RoboBullet(xPos, yPos, zPos), this, myGunarm, STORED);
	World::me->addItem(new RoboBullet(xPos, yPos, zPos), this, myGunarm, STORED);
}

void CowboyBot::print() {
	std::cout << "C";
}
