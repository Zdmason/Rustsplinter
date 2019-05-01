
#include "Gravity.h"
#include "../World.h"

#include <math.h>
#include <float.h>

Gravity::Gravity(Entity* myVictim, int initXVel, int initYVel, int initZVel, Entity* myVillain, Entity* myTarget, int turnsTillAccel) : Living() {
	order=GRAVITY;
	species="Gravity";
	isAlive=true;

	victim=myVictim;
	villain=myVillain;
	target=myTarget;
	noAccelTurns=turnsTillAccel;
	lastUpdate=World::me->curTick;

	if(noAccelTurns==-1)
	{
		noAccelTurns=0;

		if(target!=NULL)
		{
			std::queue<Square*> throwPath=World::me->tryRaypathTo(victim->xPos, victim->yPos, victim->zPos, target->xPos, target->yPos, target->zPos, true, 1);

			while(!throwPath.empty())
			{
				noAccelTurns++;
				throwPath.pop();
			}
		}
	}

	automatic=false;
	nextX=500; // How many distance units this guy is away from the edge to the next square in that direction, 1000 = 1m, 500 = halfway
	nextY=500;
	nextZ=500;
	xVel=initXVel; // How many units per second this entity is moving
	yVel=initYVel;
	zVel=initZVel;
	xAcl=0; // How many units per second per turn this entity is accelerating towards: aka, after 1000 tick's worth of time passed, vel should increase by this much total
	yAcl=0;
	zAcl=-2000;

//	double curVelocity=sqrt((xVel*xVel)+(yVel*yVel)+(zVel*zVel));

	//speed=std::max(10, std::min(1000, int(1000000.0/curVelocity)));
//	speed=250;
//	energy=speed;
	nextMoves(true);

	std::cout << "+manual gravity " << id << " on " << victim->name(1) << "- " << initXVel << "/" << initYVel << "/" << initZVel << "+ " << std::endl;
}

Gravity::Gravity(Entity* autoTarget) {
	order=GRAVITY;
	species="Gravity";
	isAlive=true;

	victim=autoTarget;
	villain=NULL;
	target=NULL;
	noAccelTurns=0;
	lastUpdate=World::me->curTick;

	automatic=true;
	nextX=500; // How many distance units this guy is away from the edge to the next square in that direction, 1000 = 1m, 500 = halfway
	nextY=500;
	nextZ=500;
	xVel=0; // How many units per second this entity is moving
	yVel=0;
	zVel=0;
	xAcl=0; // How many units per second per turn this entity is accelerating towards: aka, after 1000 tick's worth of time passed, vel should increase by this much total
	yAcl=0;
	zAcl=-2000;

	speed=250;
	energy=speed;

	std::cout << "+Auto grav " << id << " on " << victim->name(1) << " speed " << speed <<"+ ";
}


void Gravity::copy(Entity* newVictim) {
	if(newVictim->initStatus==2)
	{
		std::cout << "(Cancled copying a gravity to " << newVictim->name(2) << " because its dead) ";
		return;
	}

	Gravity* newGrav=new Gravity(newVictim, xVel, yVel, zVel, villain, target, noAccelTurns);
	newGrav->nextX=nextX;
	newGrav->nextY=nextY;
	newGrav->nextZ=nextZ;
//	newGrav->xAcl=xAcl;
//	newGrav->yAcl=yAcl; //TODO: accel should only be modified by stati, which will be copied over shorty?
//	newGrav->zAcl=zAcl;

	World::me->addGravity(newGrav);
}

void Gravity::fuseInto(Gravity* otherGrav) {
	if(!automatic) // If we're auto, we don't fuse into another gravity at all
	{
		if(otherGrav->automatic) // If the other gravity is automatic, we completely overwrite it 		TODO: right?
		{
//			otherGrav->xVel=xVel;
//			otherGrav->yVel=yVel;
//			otherGrav->zVel=zVel;
//			otherGrav->automatic=false;

//			otherGrav->xAcl=xAcl;
//			otherGrav->yAcl=yAcl;
//			otherGrav->zAcl=zAcl;

			otherGrav->addForce(xVel, yVel, zVel, villain, target, noAccelTurns, true); // TODO: either this or above, not both?

			///std::cout << "-manual override " << id << "!- " << xVel << "/" << yVel << "/" << zVel;
		}
		else //TODO: what about accel? fuse status things as well?
		{

			otherGrav->addForce(xVel, yVel, zVel, villain, target, noAccelTurns, false);
			///std::cout << "-manual fuse " << id << "!- " << xVel << "/" << yVel << "/" << zVel;
		}

//		World::me->activeQueue.update(); //TODO: can / should replace with update(this)?
	}
}

void Gravity::addForce(int xAmount, int yAmount, int zAmount, Entity* newVillain, Entity* newTarget, int turnsTillAccel, bool overwrite) {
	interrupdate();

	if(overwrite)
	{
		xVel=xAmount;
		yVel=yAmount;
		zVel=zAmount;
		villain=newVillain;
		target=newTarget;
		noAccelTurns=turnsTillAccel;
	}
	else
	{
		xVel+=xAmount;
		yVel+=yAmount;
		zVel+=zAmount;

		if(newVillain!=NULL)
		{
			villain=newVillain;
		}

		if(newTarget!=NULL)
		{
			target=newTarget;
		}
	}

	nextMoves(true);
	World::me->activeQueue.update(this);
}


void Gravity::update() {
	std::cout << "Gravity #" << id << " on " << victim->name(1) << " : ";
//	std::cout << "next / vel / speed =  " << nextX << " " << nextY << " " << nextZ << " / " << xVel << " " << yVel << " " << zVel << " / " << speed << ". "  << std::endl;

//	std::cout << "cur tick / last update is  " << World::me->curTick << " " << lastUpdate << std::endl;

	automatic=false;

	std::set<int> myMoves=nextMoves(false);

	if(myMoves.empty())
	{
		std::cout << "We're not moving anywhere in gravity update??? ";
		World::me->pause();
	}

	int xMove=(myMoves.count(1)!=0 ? 1 : (myMoves.count(-1)!=0 ? -1 : 0));
	int yMove=(myMoves.count(2)!=0 ? 1 : (myMoves.count(-2)!=0 ? -1 : 0));
	int zMove=(myMoves.count(3)!=0 ? 1 : (myMoves.count(-3)!=0 ? -1 : 0));
	double moveTime=((World::curTick-lastUpdate)/1000.0);
	lastUpdate=World::me->curTick;

	if(xMove==1)
	{
		std::cout << moveTime << " vs " << getTimeToCross(1000-nextX, xVel, xAcl) << std::endl;
	}

	nextX+=(xVel*moveTime)+(noAccelTurns>0 ? 0 : (0.5*xAcl*moveTime*moveTime));
	nextY+=(yVel*moveTime)+(noAccelTurns>0 ? 0 : (0.5*yAcl*moveTime*moveTime));
	nextZ+=(zVel*moveTime)+(noAccelTurns>0 ? 0 : (0.5*zAcl*moveTime*moveTime));

	if(xMove==-1)
	{
		nextX=1000;
	}
	else if(xMove==1)
	{
		nextX=0;
	}

	if(yMove==-1)
	{
		nextY=1000;
	}
	else if(yMove==1)
	{
		nextY=0;
	}

	if(zMove==-1)
	{
		nextZ=1000;
	}
	else if(zMove==1)
	{
		nextZ=0;
	}

	if(nextX<0 || nextY<0 || nextZ<0 || nextX>1000 || nextY>1000 || nextZ>1000)
	{
		std::cout << "one of our failed next's is less than 0 in gravity update??? " << std::endl;
		World::me->pause();
	}

	if(noAccelTurns<=0)
	{
		xVel+=xAcl*moveTime; //TODO: is this 2 S/T/T?
		yVel+=yAcl*moveTime; //TODO: is this 2 S/T/T?
		zVel+=zAcl*moveTime; //TODO: is this 2 S/T/T?  If so, something thrown up should have same velocity coming down at the same position. Does it matter?
	}
	else
	{
		noAccelTurns--;
	}


	if(nextX<0 || nextY<0 || nextZ<0 || nextX>1000 || nextY>1000 || nextZ>1000)
	{
		std::cout << "one of our failed next's is less than 0 in gravity update after accounting for celov changes??? " << std::endl;
		World::me->pause();
	}

	std::cout << "moving in the " << xMove << " " << yMove << " " << zMove << " direction: ";

	int result=victim->tryMove(victim->xPos+xMove, victim->yPos+yMove, victim->zPos+zMove, target);


	if(initStatus==2 || victim==NULL || victim->initStatus==2) // If he died from the fall damage and called dead() on this, dont bother with the rest of the stuff
	{
		std::cout << "Gravity finished from the crash: next  / vel / speed =  " << nextX << " " << nextY << " " << nextZ << " / " << xVel << " " << yVel << " " << zVel << " / " << speed << ". "  << std::endl;
		return;
	}

	if(result>0)
	{
		noAccelTurns=0; // We hit something and our gravity was manually adjusted, ignore acceleration changes over time

		nextMoves(true);

		if(!failCheck())
		{
			std::cout << "next / vel / speed =  " << nextX << " " << nextY << " " << nextZ << " / " << xVel << " " << yVel << " " << zVel << " / " << speed << ". "  << std::endl;
		}
		else
		{
			std::cout << "grav finito! " << std::endl;
		}

		return;
	}

	//TODO: stabalize in unit update instead of here
	if(victim->tags.count(FLYING)!=0 && victim->tags.count(STUNNED)==0 && victim->tags.count(ROOTED)==0)
	{
		std::cout << "(The flying victim controlled his fall) ";
		xVel=(xVel<0 ? -1 : 0)*std::max((std::abs(xVel)-3000), 0);
		yVel=(yVel<0 ? -1 : 0)*std::max((std::abs(yVel)-3000), 0);
		zVel=(zVel<0 ? -1 : 0)*std::max((std::abs(zVel)-3000), 0);
	}

	nextMoves(true);

	if(failCheck())
	{
		std::cout << "endgrav! " << std::endl;
	}
	else
	{
		std::cout << "next  / vel / speed =  " << nextX << " " << nextY << " " << nextZ << " / " << xVel << " " << yVel << " " << zVel << " / " << speed << ". "  << std::endl;
	}
}

void Gravity::interrupdate() {
	double moveTime=((World::curTick-lastUpdate)/1000.0);
	lastUpdate=World::me->curTick;

	nextX+=(xVel*moveTime)+(noAccelTurns>0 ? 0 : (0.5*xAcl*moveTime*moveTime));
	nextY+=(yVel*moveTime)+(noAccelTurns>0 ? 0 : (0.5*yAcl*moveTime*moveTime));
	nextZ+=(zVel*moveTime)+(noAccelTurns>0 ? 0 : (0.5*zAcl*moveTime*moveTime));

	if(nextX<0 || nextY<0 || nextZ<0 || nextX>1000 || nextY>1000 || nextZ>1000)
	{
		std::cout << "one of our failed next's is less than 0 in gravity interrupdate??? ";
		World::me->pause();
	}

	if(noAccelTurns<=0)
	{
		xVel+=xAcl*moveTime;
		yVel+=yAcl*moveTime;
		zVel+=zAcl*moveTime;
	}

	noAccelTurns=0;
}

std::set<int> Gravity::nextMoves(bool setSpeed) {
	// Will contain +1/2/3 for +x/y/z, and -1/2/3 for -x/y/z movement
	// setSpeed will make us adjust our speed and update us in the updateQueue to be whenever we think our next move will occur

	std::set<int> curBest;
	double bestTime=99999999;

//	std::cout << "what is bestTime for next / vel / speed =  " << nextX << " " << nextY << " " << nextZ << " / " << xVel << " " << yVel << " " << zVel << " / " << speed << ". "  << std::endl;

	for(int i=1;i<=6;i++)
	{
		int curVel =(i%3==1 ? xVel  : (i%3==2 ? yVel  : zVel));
		int curAcl =(i%3==1 ? xAcl  : (i%3==2 ? yAcl  : zAcl));
		int curDist=(i%3==1 ? 1000-nextX : (i%3==2 ? 1000-nextY : 1000-nextZ)); // If we're at 800, we only have 200 left to go. If we're going downward, we switch ina sec

		if(noAccelTurns>0)
		{
			curAcl=0;
		}

		if(curVel==0 && curAcl==0)
		{
//			std::cout  << i << " is empty, skipping " << std::endl;
			continue;
		}

		if(i>3) // 1-2-3 = try to go up to 1000, 4-5-6 = try to fall down to 0
		{
			curDist-=1000; // If we're at 800 and we though we were going upwards 200m before, now we know we're trying to go down 800m
		}

		double thisTime=0.0;

		if(curDist==0) // If we're starting on the edge, we don't want to start on our destination and always have our time be 0
		{
			if((i<=3 && curVel>0) || (i>3 && curVel<0) || (curVel==0 && ((i<=3 && curAcl>0) || (i>3 && curAcl<0))))
			{
				thisTime=0.0; // We only instantly move over it if velocity is in that direction or no velocity + acceleration in that direction
			}
			else if(curAcl==0) // If we have velocity, it woulda been caught above. If no acceleration, we're guranteed to never hit
			{
				thisTime=-1.0;
			}
			else
			{
				thisTime=getTimeToCross(0, curVel, curAcl);
			}
		}
		else
		{
			thisTime=getTimeToCross(curDist, curVel, curAcl);
		}

		if(thisTime>=0 && thisTime<=bestTime)
		{
			if(thisTime<bestTime)
			{
//				std::cout << " new best time " << thisTime << std::endl;
				bestTime=thisTime;
				curBest.clear();
			}
			else
			{
//				std::cout << " exact same time " << thisTime << std::endl;
			}

			curBest.insert(i<=3 ? i : -(i-3));
		}
		else
		{
//			std::cout << "failed slow time " << thisTime << std::endl;
		}
	}

	if(curBest.empty())
	{
		std::cout << "ERROR: empty curBest at grav nextMove " << bestTime << std::endl;
		World::me->pause();
	}

//	std::cout << "best time was" << bestTime << std::endl;

	if(setSpeed)
	{
		speed=std::max(10, std::min(1000, (int)(1000.0*bestTime)));
		energy=speed;
//		std::cout << "set speed /energy to " << speed << std::endl;
	}

	return curBest;
}

double Gravity::getTimeToCross(int distance, int initVel, int accel) {

//	std::cout << " Whats the time for dist " << distance << " : vel " << initVel << " and accel " << accel << std::endl;

	if(initVel==0 && accel==0)
	{
//		std::cout << " no movement, skipping " << std::endl;
		return -1;
	}

	if(accel==0)
	{
		double thisTime=(0.0+distance)/initVel;
//		std::cout << " no accel means time is " << thisTime << std::endl;

		return thisTime;
	}
	else if(((initVel*initVel)+(2.0*accel*distance))<0)
	{
//		std::cout << " negative square root top = not possible " << std::endl;
		return -1;
	}

	double result=((sqrt(((0.0+initVel)*(0.0+initVel))+(2.0*accel*distance)))-(0.0+initVel))/(0.0+accel);
//	std::cout << (((0.0+initVel)*(0.0+initVel))+(2.0*accel*distance)) << " is sqrted to " << sqrt(((0.0+initVel)*(0.0+initVel))+(2.0*accel*distance)) << " minus " << (0.0+initVel) << " divided by " << (0.0+accel) << " to make " << result << std::endl;

	if(result>0)
	{
//		std::cout << " new best time " << result << std::endl;
		return result;
	}

	result=((-sqrt(((0.0+initVel)*(0.0+initVel))+(2.0*accel*distance)))-(0.0+initVel))/(0.0+accel);
//	std::cout << (((0.0+initVel)*(0.0+initVel))+(2.0*accel*distance)) << " is sqrted to " << -sqrt(((0.0+initVel)*(0.0+initVel))+(2.0*accel*distance)) << " minus " << (0.0+initVel) << " divided by " << (0.0+accel) << " to make " << result << std::endl;

	if(result>0)
	{
//		std::cout << " new best time " << result << std::endl;
		return result;
	}

//	std::cout << " both times here at getTimeToCross failed " << result << std::endl;
	return -1;
}


void Gravity::fullRefresh() {
	std::cout << "!!! gravities's version of fullRefresh is being called when it shouldn't be?";
	World::me->pause();
}

bool Gravity::refresh() {
	return true;
}


bool Gravity::failCheck() {
	// MAKE SURE we've done a nextMoves(true) call before this to ensure we're at the correct speed. Currently this is only called in update

	if(std::abs(xVel)<1000 && std::abs(yVel)<1000 && std::abs(zVel)<1000 && !victim->fallCheck())
	{
		std::cout << "The victim slowed to a halt! " << xVel << " " << yVel << " " << zVel << std::endl;
		World::me->remGravity(this);
		return true;
	}

	return false;
}

void Gravity::claim(Entity* thing) {
	if(totalVictim.count(thing)!=0)
	{
		std::cout << name(2) << " trying to claim " << thing->name(2) << " but is already part of our field?" << std::endl;
		World::me->pause();
	}

	victim=thing;

	if(thing->order==UNIT)
	{
		victim->myGrav=this;
		totalVictim.insert(thing);

		Unit* guy=dynamic_cast<Unit*>(thing);

		guy->drop(NULL, false);
		guy->dropped(NULL, false);

		std::vector<Item*> guyBlob=guy->getBlob(true, 1, 3, 3, NULL, 0, 0);
		for(unsigned int i=0;i<guyBlob.size();i++)
		{
			if(totalVictim.count(guyBlob[i])!=0)
			{
				std::cout << name(2) << " trying to gravclaim " << thing->name(2) << " but one of his blob is already ours???" << std::endl;
				World::me->pause();
			}

			guyBlob[i]->myGrav=this;
			totalVictim.insert(guyBlob[i]);
		}
	}
	else if(thing->order==ITEM)
	{
		Item* obj=dynamic_cast<Item*>(thing);

		while(!obj->holders.empty())
		{
			(*obj->holders.begin())->drop(false);
		}

		std::vector<Item*> objBlob=obj->getBlob(1, 1, 3, 3, NULL, 0, 0);
		for(unsigned int i=0;i<objBlob.size();i++)
		{
			if(totalVictim.count(objBlob[i])!=0)
			{
				std::cout << name(2) << " trying to gravclaim " << thing->name(2) << " but one of his blob is already ours?" << std::endl;
				World::me->pause();
			}

			objBlob[i]->myGrav=this;
			totalVictim.insert(objBlob[i]);
		}
	}
	else
	{
		thing->myGrav=this;
		totalVictim.insert(thing);
	}

	World::me->handleRefresh();
}


void Gravity::disown(Entity* thing) {
	if(totalVictim.count(thing)==0)
	{
		std::cout << name(2) << " trying to gravdisown " << thing->name(2) << " but isnt part of our field?" << std::endl;
		World::me->pause();
	}

	if(thing->order==UNIT)
	{
		totalVictim.erase(thing);
		thing->myGrav=NULL;

		Unit* guy=dynamic_cast<Unit*>(thing);

		std::vector<Item*> guyBlob=guy->getBlob(true, 1, 3, 3, NULL, 0, 0);
		for(unsigned int i=0;i<guyBlob.size();i++)
		{
			if(totalVictim.count(guyBlob[i])==0)
			{
				std::cout << name(2) << " trying to gravdisown " << thing->name(2) << " but one of his blob doesnt have my grav?" << std::endl;
				World::me->pause();
			}

			totalVictim.erase(guyBlob[i]);
			guyBlob[i]->myGrav=NULL;
		}
	}
	else if(thing->order==ITEM)
	{
		Item* obj=dynamic_cast<Item*>(thing);

		if(obj->owner!=NULL)
		{
			std::cout << "gravdisown " << thing->name(2) << "'s owner" << std::endl;
			disown(obj->owner);
			return;
		}

		std::vector<Item*> objBlob=obj->getBlob(1, 3, 3, 3, NULL, 0, 0);
		for(unsigned int i=0;i<objBlob.size();i++)
		{
			if(totalVictim.count(objBlob[i])==0)
			{
				std::cout << name(2) << " trying to gravdisown " << thing->name(2) << " but one of his blob doesnt have my grav?" << std::endl;
				World::me->pause();
			}

			totalVictim.erase(objBlob[i]);
			objBlob[i]->myGrav=NULL;
		}
	}
	else
	{
		totalVictim.erase(thing);
		thing->myGrav=NULL;
	}

	if(totalVictim.empty())
	{
		victim=NULL;
		World::me->remGravity(this);
		return;
	}

	if(totalVictim.count(victim)==0)
	{
		victim=(*totalVictim.begin());
	}
}
