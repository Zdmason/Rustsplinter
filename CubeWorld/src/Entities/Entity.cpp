
#include "Entity.h"
#include "../World.h"

#include "../Actions/Attacks/Melee/MeleeAttack.h"

#include <iostream>
#include <cstdio>
#include <math.h>
#include <float.h>

Entity::Entity(int x, int y, int z) : Living() {
	order=ENTITY;

	xPos=x;
	yPos=y;
	zPos=z;
	// tags initialized as empty set
	// soloTags initialized as empty set
	// duoTags initialized as empty set

	myGrav=NULL;
	// Stati initialized as an empty vector
	//visible=true;
	isHidden=false;
	worked=false;
	//size=-2;
	// seekers initialized as empty list
}

Entity::~Entity() {
	;
}


int Entity::canMove(Square* here, Square* there) {
	// Should return: -3 = out of bounds target, -2 = couldn't letMove, -1 = already at target square, 0 = moved, 1+ = id of blocking entity

	//TODO: When would we use canFall instead of canMove?

	std::cout << "!!! Entity's version of canMove is being called when it should be something else's?";
	World::me->pause();
	return 0;
}

int Entity::canPlanMove(Square* here, Square* there) {
	// Should return: -3 = out of bounds target, -2 = couldn't letMove, -1 = already at target square, 0 = moved, 1+ = id of blocking entity

	//TODO: When would we use canFall instead of canMove?

	std::cout << "!!! Entity's version of canPlanMove is being called when it should be something else's?";
	World::me->pause();
	return 0;
}

int Entity::canBlink(Square* here, Square* there) {
	// Should return: -3 = out of bounds target, -2 = couldn't letMove, -1 = already at target square, 0 = moved, 1+ = id of blocking entity

	std::cout << "!!! Entity's version of canBlink is being called when it should be something else's?";
	World::me->pause();
	return 0;
}

int Entity::tryMove(int x, int y, int z, Entity* collideTarget) {
	// Should return: -3 = out of bounds target, -2 = couldn't letMove, -1 = already at target square, 0 = moved, 1+ = id of blocking entity

	std::cout << "!!! Entity's version of trymove is being called when it should be something else's?";
	World::me->pause();
	return 0;
}

void Entity::moved(int x, int y, int z, int oldX, int oldY, int oldZ) {
	std::cout << "!!! Entity's version of move is being called when it should be something else's?";
	World::me->pause();
}


bool Entity::letInfect(Status* effect) {
	std::vector<Status*> afflictions=stati;
	for(unsigned int i=0;i<afflictions.size();i++)
	{
		if(!afflictions[i]->letInfect(effect))
		{
			return false;
		}
	}

	return true;
}

bool Entity::letSelfInfect(Status* effect) {
	return true;
}

void Entity::damage(int impactHit, int slashHit, int stabHit, int brokeHit, int maxHit, int soulHit, Entity* cause, Entity* source, bool canEmbed) {
	// Cause = what's hitting us, source = who's to blame for this shit

	std::cout << "!!! Entity's version of damage is being called when it should be something else's?";
	World::me->pause();
}

int Entity::totalWeight() {
	std::cout << "!!! Entity's version of totalWeight is being called when it should be something else's?";
	World::me->pause();
	return -1;
}

void Entity::collide(Entity* victim, bool spread) {
	// TODO: what here? should this be here?

	if(World::me->distance(xPos, yPos, zPos, victim->xPos, victim->yPos, victim->zPos)>=2) // TODO: remove this and below if can blink into collide?
	{
		std::cout << "!!! An entity is colliding with someone more than 1 square away?";
		World::me->pause();
		return;
	}

//	if(!canMove(World::me->cube[xPos][yPos][zPos], World::me->cube[xPos][yPos][zPos]))
//	{
//		std::cout << "!!! An entity is colliding with someone it cant move to?";
//		World::me->pause();
//		return;
//	}

	// TODO: status effects that spread on collision: fire, infections, etc

	//TODO: finish gravity effects here, remove shit from gravity, change enity canfall to canmove?

	if(spread)
	{
		std::cout << "Collision between " << name(1) << " and " << victim->name(1) << "! ";

		victim->collide(this, false);

		bool sameSquare=(victim->xPos==xPos && victim->yPos==yPos && victim->zPos==zPos); // TODO: if ever multisquare things, change this

		if(!sameSquare && (myGrav!=NULL || victim->myGrav!=NULL))
		{
			int totalImpactSpeed=0;

			// totalDamage is currently totalVelocity towards eachother, convert after adding together

			// XXX: yes it SHOULD be both added together: 2 seperate damages counts armor twice, and both victims should take one instance of damage
			if(myGrav!=NULL)
			{
				// TODO: interrupdate before hitting? say something has acceleration in a direction, currently we only have it saved from when it started its turn, aka at the edge of its square

				std::cout << std::endl  << "my grav before: " << myGrav->xVel << " "  << myGrav->yVel << " " << myGrav->zVel << std::endl;

				if(myGrav->xVel!=0 && victim->xPos!=xPos)
				{
					totalImpactSpeed+=std::abs((int)myGrav->xVel);
					myGrav->xVel/=-4;
					myGrav->xVel-=(myGrav->xVel>0 ? std::min(myGrav->xVel, 300) : std::max(myGrav->xVel, -300));
					myGrav->nextX=500;
				}
				if(myGrav->yVel!=0 && victim->yPos!=yPos)
				{
					totalImpactSpeed+=std::abs((int)myGrav->yVel);
					myGrav->yVel/=-4;
					myGrav->yVel-=(myGrav->yVel>0 ? std::min(myGrav->yVel, 300) : std::max(myGrav->yVel, -300));
					myGrav->nextY=500;
				}
				if(myGrav->zVel!=0 && victim->zPos!=zPos)
				{
					totalImpactSpeed+=std::abs((int)myGrav->zVel);
					myGrav->zVel/=-4;
					myGrav->zVel-=(myGrav->zVel>0 ? std::min(myGrav->zVel, 300) : std::max(myGrav->zVel, -300));
					myGrav->nextZ=500;
				}

				// TODO: based on friction
				myGrav->xVel/=2;
				myGrav->yVel/=2;
				myGrav->zVel/=2;

				std::cout << std::endl  << "my grav after: " << myGrav->xVel << " "  << myGrav->yVel << " " << myGrav->zVel << std::endl;
			}

			if(victim->myGrav!=NULL)
			{
				if(victim->myGrav->xVel!=0 && xPos!=victim->xPos)
				{
					totalImpactSpeed+=std::abs((int)victim->myGrav->xVel);
					victim->myGrav->xVel/=-4;
					victim->myGrav->xVel-=(victim->myGrav->xVel>0 ? std::min(victim->myGrav->xVel, 300) : std::max(victim->myGrav->xVel, -300));
					victim->myGrav->nextX=500;
				}
				if(victim->myGrav->yVel!=0 && yPos!=victim->yPos)
				{
					totalImpactSpeed+=std::abs((int)victim->myGrav->yVel);
					victim->myGrav->yVel/=-4;
					victim->myGrav->yVel-=(victim->myGrav->yVel>0 ? std::min(victim->myGrav->yVel, 300) : std::max(victim->myGrav->yVel, -300));
					victim->myGrav->nextY=500;
				}
				if(victim->myGrav->zVel!=0 && zPos!=victim->zPos)
				{
					totalImpactSpeed+=std::abs((int)victim->myGrav->zVel);
					victim->myGrav->zVel/=-4;
					victim->myGrav->zVel-=(victim->myGrav->zVel>0 ? std::min(victim->myGrav->zVel, 300) : std::max(victim->myGrav->zVel, -300));
					victim->myGrav->nextZ=500;
				}


				// TODO: based on friction
				victim->myGrav->xVel/=2;
				victim->myGrav->yVel/=2;
				victim->myGrav->zVel/=2;
			}

			int extraHits[5]={0, 0, 0, 0, 0};

			int bestTotal=-1;

			if(order==ITEM)
			{
				Item* obj=dynamic_cast<Item*>(this);
				for(unsigned int i=0;i<obj->selfActions.size();i++)
				{
					if((obj->selfActions[i]->actionType==COMBAT) && (obj->selfActions[i]->actionSubtype==MELEE)) // TODO: && is a default attack: if gloves add a karate chop, we don't use it
					{
						MeleeAttack* act=dynamic_cast<MeleeAttack*>(obj->selfActions[i]);

						int thisTotal=std::min(act->slashScale*totalImpactSpeed, act->slashMax)+std::min(act->stabScale*totalImpactSpeed, act->stabMax)+act->brokeDamage+act->maxDamage+act->soulDamage;
						if(thisTotal>bestTotal)
						{
							bestTotal=thisTotal;
							extraHits[0]=std::min(act->slashScale*totalImpactSpeed, act->slashMax);
							extraHits[1]=std::min(act->stabScale*totalImpactSpeed, act->stabMax);
							extraHits[2]=act->brokeDamage;
							extraHits[3]=act->maxDamage;
							extraHits[4]=act->soulDamage;
							std::cout << act->name << " changes new damage ratio to " << bestTotal << std::endl;
						}
					}
				}
			}

			victim->damage((totalImpactSpeed*totalWeight()/World::me->forcePerDamage), extraHits[0], extraHits[1], extraHits[2], extraHits[3], extraHits[4], this, this, true);

			// TODO: also after: victim hits us with same collision force, but only once we dicide that the above is correct

			std::cout << std::endl  << "Total damage: " << (totalImpactSpeed*totalWeight()/World::me->forcePerDamage) << " + " << bestTotal << std::endl;
		}
		else
		{
			std::cout << std::endl  << "NO GRAVITY DETECTED? " << std::endl;
		}
	}
}

bool Entity::addGravForce(int xAmount, int yAmount, int zAmount, Entity* villain, Entity* target, bool overwrite) {
	// Use this if you're sure you're good with the exact amounts you're adding in the directions that it's gonna be launched in
	// Returns true if we made a new gravity for this, false if we already had one and we're just adding the force on

	if(myGrav==NULL)
	{
		World::me->addGravity(new Gravity(this, xAmount, yAmount, zAmount, villain, target, -1));
		return true;
	}

	myGrav->addForce(xAmount, yAmount, zAmount, villain, target, 0, overwrite);
	return false;
}

bool Entity::addGravForce(int xDist, int yDist, int zDist, Entity* villain, Entity* target, int amount) {
	// Make a gravForce by equalizing the x/y/zDist normalized around the amount

	// 1000/1,0,0: distance is 1,        mult is 1k,  force becomes 1000, 0, 0,  works
	// 1000/1,1,0: distance is sqrt(2),  mult is 707, force becomes 707, 707, 0, works
	// 1000/5,5,0: distance is sqrt(50), mult is 141, force becomes 707, 707, 0, works
	// 1000/5,1,0: distance is sqrt(26), mult is 196, force becomes 980, 196, 0, works

	double dist=World::me->distance(0, 0, 0, xDist, yDist, zDist);
	double multiplier=(0.0+amount)/dist;
	return addGravForce(multiplier*xDist, multiplier*yDist, multiplier*zDist, villain, target, false);
}

bool Entity::addGravForce(int amount, Entity* thing, int targetLevel, Entity* villain) {
	// targetLevel: 0 = thing is an exploder that we're being pushed away from at velocity amount
	//              1 = thing is the target we're being thrown at with velocity amount
	//              2 = same as 1, but its also the target we're aiming for

	if(thing==NULL)
	{
		std::cout << "gravforce needs a non-null source here";
		World::me->pause();
		return false;
	}

	if(thing->xPos==xPos && thing->yPos==yPos && thing->zPos==zPos)
	{
		// TODO: what here, if the source and the thing are in the exact same square?
		return addGravForce(0, 0, 1, villain, NULL, amount);
	}

	if(targetLevel==0) // If thing is exploding and we're being pushed away from it
	{
		return addGravForce(xPos-thing->xPos, yPos-thing->yPos, zPos-thing->zPos, villain, NULL, amount);
	}
	else // If thing is our target and we're aiming towards it
	{
		return addGravForce(thing->xPos-xPos, thing->yPos-yPos, thing->zPos-zPos, villain, (targetLevel==2 ? thing : NULL), amount);
	}

}


std::vector<Living*> Entity::refreshBlob() {
	std::cout << "!!! Entity's version of trydie is being called when it should be overwritten?";
	World::me->pause();
	std::vector<Living*> fail;
	return fail;
}

void Entity::retag(std::multiset<Tag>* sharedTags) {
	std::cout << "!!! Entity's version of trydie is being called when it should be overwritten?";
	World::me->pause();
}

bool Entity::fallCheck() {
	// Returns true if we're by default falling to the ground right now

	if(initStatus==2)
	{
		return false;
	}

	if(tags.count(FLYING)!=0 && tags.count(STUNNED)==0 && tags.count(ROOTED)==0)
	{
		return false;
	}

	if(World::me->cube[xPos][yPos][zPos]->block->NotZ<2 && World::me->cube[xPos][yPos][zPos-1]->block->Z<2 && World::me->cube[xPos][yPos][zPos-1]->block->center<2)
	{
		if(tags.count(STUNNED)!=0 || World::me->cube[xPos][yPos][zPos]->block->center==0)
		{
			return true;
		}
	}
	return false;
}


void Entity::tryDie() {
	std::cout << "!!! Entity's version of trydie is being called when it should be overwritten?";
	World::me->pause();
}

bool Entity::letDie(Entity* dier) {
	return true;
}

void Entity::onDie() {
	;
}


void Entity::print() {
	std::cout << species << " didn't override print()" << std::endl;
	World::me->pause();
}
