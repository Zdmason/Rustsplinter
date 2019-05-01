
#ifndef GRAVITY_H_
#define GRAVITY_H_

#include "../Entities/Entity.h"

class Gravity : public Living {
public:
	Gravity(Entity* myVictim, int initXVel, int initYVel, int initZVel, Entity* myVillain, Entity* myTarget, int turnsTillAccel);
	Gravity(Entity* autoTarget);
	//~Gravity();

	Entity* victim;
	std::set<Entity*> totalVictim;
	Entity* villain;
	Entity* target;
	int noAccelTurns; // Turns we don't count acceleration, so we can throw things in a straight line for a distance // TODO: any better way?
	int lastUpdate;

	bool automatic;
	int nextX;
	int nextY;
	int nextZ;
	int xVel; // Velocity is Squares per (1000 ticks / 1 turn), gravity is 1 S/T
	int yVel;
	int zVel;
	int xAcl;
	int yAcl;
	int zAcl;

	void copy(Entity* newVictim);
	void fuseInto(Gravity* otherGrav);
	void addForce(int xAmount, int yAmount, int zAmount, Entity* newSource, Entity* newTarget, int turnsTillAccel, bool overwrite);

	void update();
	void interrupdate();
	std::set<int> nextMoves(bool setSpeed);
	double getTimeToCross(int distance, int initVel, int accel);

	void fullRefresh();
	bool refresh();

	bool failCheck();
	void claim(Entity* thing);
	void disown(Entity* thing);
};

#endif /* GRAVITY_H_ */
