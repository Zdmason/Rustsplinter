
#include "Item.h"
#include "..\..\World.h"
#include "..\..\Physics\Gravity.h"

Item::Item(int x, int y, int z) : Entity(x, y, z) {
	order=ITEM;
	//genus=NONE;

	isHidden=true;

	owner=NULL;
	brokeHp=0;
	severHp=0;
	maxHp=0;
	maxMaxHp=0;

	weight=1;
	strength=3;

	// attached init as empty set
	holding=NULL;
	// holders init as empty set
	// armoring init as empty set
	armor=NULL;
	// storing init as empty set
	storer=NULL;
	// embedded init as empty set
	embedding=NULL;
}

Item::~Item() {
	; // todo: make this
}

void Item::update() {
	std::cout << name(2) << ": ";

	if(energy!=0)
	{
		std::cout << "??? " << name(2) << " is updating even though my energy is " << energy << "???";
		World::me->pause();
	}

	worked=false;

	std::vector<Status*> afflictions=stati;
	for(unsigned int i=0;i<afflictions.size();i++)
	{
		afflictions[i]->subwork();
	}

//	std::list<Item*> helding=holding;
//	for(std::list<Item*>::iterator held=helding.begin(); held!=helding.end(); held++)
//	{
//		(*held)->work();
//	}

	if(!worked && tags.count(STUNNED)==0 && tags.count(FALLING)==0)
	{
		work();
	}
	else if(tags.count(FALLING)==0)
	{
		std::cout << "Falling... ";
	}
	else if(tags.count(STUNNED)!=0)
	{
		std::cout << "Stunned... ";
	}
	else if(worked)
	{
		std::cout << "Already worked... ";
	}

	energy=speed;

	std::cout << std::endl;
}

void Item::subwork() {
	;
}


int Item::canMove(Square* here, Square* there) {
	// Returns: -2 = couldn't letMove, -1 = same square, 0 = canMove, 1+ = id of blocking entity

	if(here==there)
	{
		std::cout << "Why is item " << name(2) << " trying to canPlanMoveto the same square?";
		World::me->pause();
		return -666;
	}

	if(World::me->distance(here->xPos, here->yPos, here->zPos, there->xPos, there->yPos, there->zPos) >= 2)
	{
		std::cout << "Why is item " << name(2) << " trying to canFall more than one square away?";
		World::me->pause();
		return -666;
	}

	int minBlocking=0;

	int xMove=0;
	if(here->xPos > there->xPos)
	{
		xMove=-1;
		minBlocking++;
	}
	else if(here->xPos < there->xPos)
	{
		xMove=1;
		minBlocking++;
	}

	int yMove=0;
	if(here->yPos > there->yPos)
	{
		yMove=-1;
		minBlocking++;
	}
	else if(here->yPos < there->yPos)
	{
		yMove=1;
		minBlocking++;
	}

	int zMove=0;
	if(here->zPos > there->zPos)
	{
		zMove=-1;
		minBlocking++;
	}
	else if(here->zPos < there->zPos)
	{
		zMove=1;
		minBlocking++;
	}

	if(minBlocking==0)
	{
		std::cout << "Why is item " << name(2) << " failing hard at minBlocking?";
		World::me->pause();
		return -666;
	}
	else if(minBlocking==1)
	{
		minBlocking=2;
	}
	else
	{
		minBlocking=4;
	}

	for(int i=std::min(0, xMove); i<=std::max(0, xMove);i++)
	{
		for(int j=std::min(0, yMove); j<=std::max(0, yMove);j++)
		{
			for(int k=std::min(0, zMove); k<=std::max(0, zMove);k++)
			{
				if(xMove!=0)
				{
					if(i==std::min(0, xMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->X>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
					else if(i==std::max(0, xMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->NotX>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
				}

				if(yMove!=0)
				{
					if(j==std::min(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->Y>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
					else if(j==std::max(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->NotY>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
				}

				if(zMove!=0)
				{
					if(k==std::min(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->Z>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
					else if(k==std::max(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->NotZ>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
				}
			}
		}
	}

	if(there->block->center==3)
	{
		return there->block->id; //todo: do we care if we're moving from inside a solid block?
	}

	if(there->nogo)
	{
		return there->block->id;
	}

	return 0;

	//  #'s 	Sizes			is blocked by
	// -------------------------------------------
	//   0   	ghosts  		sealed
	//   1   	flying / gas  	solid walls
	//   2   	tiny / items  	buildings
	//   3   	small  			buildings
	//   4   	medium  		buildings
	//   5   	huge 			buildings
	//   6  	building		tiny / items
	//   7   	solid wall		flying / gas
	//   8   	sealed	 		anything


	/*
	std::list<Unit*>::iterator thing;
	if(place->units.empty())
	{
		return true;
	}
	else if(place->sizeList[8]!=0)
	{
		return false;
	}
	else if(size==0 || tags.count(PHASING)!=0)
	{
		return true;
	}
	else if(!visible)
	{
		return place->sizeList[6]==0;
	}
	else if(place->sizeList[7]!=0)
	{
		return false;
	}
	else if(size==1 || tags.count(FLYING)!=0)
	{
		//TODO: should these be changed? if not, merge all into if(size<=5)
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->size==6 && (*thing)->tags.count(PHASING)==0 && (*thing)->visible)
			{
				return false;
			}
		}

		return true;
	}
	else if(size==2)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->size>=6 && (*thing)->tags.count(PHASING)==0 && (*thing)->visible)
			{
				return false;
			}
		}

		return true;
	}
	else if(size==3)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->size>=6 && (*thing)->tags.count(PHASING)==0 && (*thing)->visible)
			{
				return false;
			}
		}

		return true;
	}
	else if(size==4)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->size>=6 && (*thing)->tags.count(PHASING)==0 && (*thing)->visible)
			{
				return false;
			}
		}

		return true;
	}
	else if(size==5)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->size>=6 && (*thing)->tags.count(PHASING)==0 && (*thing)->visible)
			{
				return false;
			}
		}

		return true;
	}

	return false;
	*/
}

int Item::canPlanMove(Square* here, Square* there) {
	// Returns: -2 = couldn't letMove, -1 = same square, 0 = canMove, 1+ = id of blocking entity

	if(here==there)
	{
		std::cout << "Why is item " << name(2) << " trying to canPlanMoveto the same square?";
		World::me->pause();
		return -666;
	}

	if(World::me->distance(here->xPos, here->yPos, here->zPos, there->xPos, there->yPos, there->zPos) >= 2)
	{
		std::cout << "Why is item " << name(2) << " trying to canPlanMove more than one square away?";
		World::me->pause();
		return -666;
	}

	int minBlocking=0;

	int xMove=0;
	if(here->xPos > there->xPos)
	{
		xMove=-1;
		minBlocking++;
	}
	else if(here->xPos < there->xPos)
	{
		xMove=1;
		minBlocking++;
	}

	int yMove=0;
	if(here->yPos > there->yPos)
	{
		yMove=-1;
		minBlocking++;
	}
	else if(here->yPos < there->yPos)
	{
		yMove=1;
		minBlocking++;
	}

	int zMove=0;
	if(here->zPos > there->zPos)
	{
		zMove=-1;
		minBlocking++;
	}
	else if(here->zPos < there->zPos)
	{
		zMove=1;
		minBlocking++;
	}

	if(minBlocking==0)
	{
		std::cout << "Why is item " << name(2) << " failing hard at minBlocking?";
		World::me->pause();
		return -666;
	}
	else if(minBlocking==1)
	{
		minBlocking=2;
	}
	else
	{
		minBlocking=4;
	}

	for(int i=std::min(0, xMove); i<=std::max(0, xMove);i++)
	{
		for(int j=std::min(0, yMove); j<=std::max(0, yMove);j++)
		{
			for(int k=std::min(0, zMove); k<=std::max(0, zMove);k++)
			{
				if(xMove!=0)
				{
					if(i==std::min(0, xMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->X>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
					else if(i==std::max(0, xMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->NotX>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
				}

				if(yMove!=0)
				{
					if(j==std::min(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->Y>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
					else if(j==std::max(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->NotY>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
				}

				if(zMove!=0)
				{
					if(k==std::min(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->Z>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
					else if(k==std::max(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->NotZ>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
				}
			}
		}
	}

	if(there->block->center==3)
	{
		return there->block->id; //todo: do we care if we're moving from inside a solid block?
	}

	if(there->nogo)
	{
		return there->block->id;
	}

	return 0;

	//  #'s 	Sizes			is blocked by
	// -------------------------------------------
	//   0   	ghosts  		sealed
	//   1   	flying / gas  	solid walls
	//   2   	tiny / items  	buildings
	//   3   	small  			buildings
	//   4   	medium  		buildings
	//   5   	huge 			buildings
	//   6  	building		tiny / items
	//   7   	solid wall		flying / gas
	//   8   	sealed	 		anything


	/*
	std::list<Unit*>::iterator thing;
	if(place->units.empty())
	{
		return true;
	}
	else if(place->sizeList[8]!=0)
	{
		return false;
	}
	else if(size==0 || tags.count(PHASING)!=0)
	{
		return true;
	}
	else if(!visible)
	{
		return place->sizeList[6]==0;
	}
	else if(place->sizeList[7]!=0)
	{
		return false;
	}
	else if(size==1 || tags.count(FLYING)!=0)
	{
		//TODO: should these be changed? if not, merge all into if(size<=5)
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->size==6 && (*thing)->tags.count(PHASING)==0 && (*thing)->visible)
			{
				return false;
			}
		}

		return true;
	}
	else if(size==2)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->size>=6 && (*thing)->tags.count(PHASING)==0 && (*thing)->visible)
			{
				return false;
			}
		}

		return true;
	}
	else if(size==3)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->size>=6 && (*thing)->tags.count(PHASING)==0 && (*thing)->visible)
			{
				return false;
			}
		}

		return true;
	}
	else if(size==4)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->size>=6 && (*thing)->tags.count(PHASING)==0 && (*thing)->visible)
			{
				return false;
			}
		}

		return true;
	}
	else if(size==5)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->size>=6 && (*thing)->tags.count(PHASING)==0 && (*thing)->visible)
			{
				return false;
			}
		}

		return true;
	}

	return false;
	*/
}

int Item::tryMove(int x, int y, int z, Entity* target) {
	// Returns: -3 = out of bounds, -2 = letMove stopped, -1 = targeted same square, 0 = moved, 1+ = id of blocking entity

	if(xPos==x && yPos==y && zPos==z) //TODO: Should we do this if we don't have any move actions?
	{
		return -1;
	}

	//TODO: check if other items let this be moved

	if(!letMove(x, y, z))
	{
		return -2;
	}

	//TODO: other preventions

	int hitResult=canMove(World::me->cube[xPos][yPos][zPos], World::me->cube[x][y][z]);

	if(hitResult>=0 && target!=NULL && target->xPos==x && target->yPos==y && target->zPos==z)
	{
		hitResult=target->id;
	}

	if(hitResult!=0)
	{
		if(hitResult<=0)
		{
			std::cout << "A " << name(2) << " is trying to tryMove, but went up to checking canMove and got " << hitResult << " instead of an id?" ;
			World::me->pause();
			return -666;
		}

		collide(World::me->getEntId(hitResult), true);
		return hitResult;
	}

	if(World::me->cube[x][y][z]->nogo)
	{
		std::cout << "A " << name(2) << " is trying to tryMove into a nogo zone, but didn't get blocked up to its attempt to move?" ;
		World::me->pause();
		return World::me->cube[x][y][z]->block->id;
	}

	if(x<=0 || x>=World::me->xMax-1 || y<=0 || y>=World::me->yMax-1 || z<=0 || z>=World::me->zMax-1)
	{
		return -3;
	}

	World::me->moveItem(this, x, y, z);
	return 0;
}

void Item::moved(int x, int y, int z, int oldX, int oldY, int oldZ) {
	if(owner==NULL && myGrav==NULL && fallCheck() && initStatus!=2)
	{
		std::cout << "(" << name(2) << " started to itemfall!) ";
		World::me->addGravity(new Gravity(this));
	}
}

int Item::throwAt(Entity* target, int x, int y, int z, int amount) {
	// THIS is being thrown at the target / location, NOT whatever this is holding
	// -2 = can't throw?, -1 = thrown at target but missed?, 0 = success, 1+ = id of non-target entity hit

	if(holders.empty())
	{
		std::cout << "ERROR: trying to throw " << name(2) << " but it has no holders? ";
		World::me->pause();
		return -666;
	}

	if(bestCarryLevel(NULL)==3)
	{
		std::cout << "ERROR: trying to throw " << name(2) << " but its an organ? ";
		World::me->pause();
		return -666;
	}

	fullDrop(false);

	if(target==NULL && x<=-1)
	{
		std::cout << "ERROR: trying to throw " << name(2) << " but it has no target / target pos? ";
		World::me->pause();
		World::me->handleRefresh();
		return -666;
	}

	int realX=(target!=NULL ? target->xPos : x);
	int realY=(target!=NULL ? target->yPos : y);
	int realZ=(target!=NULL ? target->zPos : z);

	// TODO: arm strength here for how hard we can throw this

	std::cout << "[Threw " << name(1) << " at " << (target==NULL ? "" : target->name(0)) << " " << realX << " " << realY << " " << realZ <<  "] ";
	addGravForce(amount, target, 2, NULL);
	World::me->handleRefresh();
	return 0;







	Entity* realTarget=target;

	if(realTarget==NULL)
	{
		realTarget=World::me->tryTargetTo(xPos, yPos, zPos, x, y, z, true, 1);

		if(realTarget==NULL)
		{
			std::cout << "[Threw " << name(2) << " to " << x << " " << y << " " << z << " with no interruptions] ";

			std::queue<Square*> throwPath=World::me->tryRaypathTo(xPos, yPos, zPos, x, y, z, true, 1);
			while(!throwPath.empty())
			{
				World::me->moveItem(this, throwPath.front()->xPos, throwPath.front()->yPos, throwPath.front()->zPos);
				throwPath.pop();
			}

			World::me->handleRefresh();
			return 0;
		}

		// TODO: throwing a slash / pierce item = can slash through multiple people at once if they kill the target?
	}
	else
	{
		realTarget=World::me->tryTargetTo(xPos, yPos, zPos, target->xPos, target->yPos, target->zPos, true, 1);
		if(realTarget==NULL)
		{
			realTarget=target;
		}
	}

	std::queue<Square*> throwPath=World::me->tryRaypathTo(xPos, yPos, zPos, realTarget->xPos, realTarget->yPos, realTarget->zPos, true, 1);
	while(!throwPath.empty())
	{
		World::me->moveItem(this, throwPath.front()->xPos, throwPath.front()->yPos, throwPath.front()->zPos);
		throwPath.pop();
	}

	std::cout << "[thrown hit " << realTarget->name(2) << " with " << name(2) << " for 50 hp] ";
	realTarget->damage(50, 0, 0, 10, 0, 0, this, NULL, true); // TODO: keep track of who threw it and put here

	World::me->handleRefresh();
	return (target==realTarget ? 0 : realTarget->id);
}


void Item::damage(int impactHit, int slashHit, int stabHit, int brokeHit, int maxHit, int soulHit, Entity* cause, Entity* source, bool canEmbed) {
	// Impact hit should be speed * weight for collisions, or str * impactScale * weight for melee attacks. AKA: huge numbers that we'll reduce here

	damage(impactHit, slashHit, stabHit, brokeHit,  maxHit, soulHit, cause, source, true, canEmbed, this);
}

void Item::damage(int impactHit, int slashHit, int stabHit, int brokeHit, int maxHit, int soulHit, Entity* cause, Entity* villain, bool canEmbed, bool armorCheck, Item* realTarget) {

	// TODO: spreading damage: if someone gravity falls from 100k ft onto the floor and hits their head, any excess damage done should spread to the body

	if(armorCheck && armor!=NULL)
	{
		// TODO: if we target someone's heart, the damage should aim for this piece only if our armor is armoring anything else besides us
		armor->damage(brokeHit, impactHit, slashHit, stabHit, maxHit, soulHit, cause, villain, canEmbed, true, realTarget);
		return;
	}

	// TODO MAYBE: full break damage doesn't remove the item, instead causes all damage to reduce max hp?
	// above makes it like if where you can mutilate a body part till its cloven and whatnot

	if(soulHit>0 && owner!=NULL)
	{
		// TODO: soul hitting something attached but not "alive" of us, aka chestplate armor, shouldn't take soul damage

		owner->soulHp-=soulHit;
		if(owner->soulHp<=0)
		{
			World::me->remUnit(owner);
		}
	}

	int realBrokeHit=brokeHit;

	if(stabHit>0)
	{
		std::vector<Item*> stabable; // Stabable parts we're armor covering or being stored inside us
		bool found=false;

		std::set<Item*>::iterator possibleHit;
		for(possibleHit=attached.begin(); possibleHit!=attached.end();possibleHit++)
		{
			if((*possibleHit)->armor==this)
			{
				stabable.push_back(*possibleHit);

				if((*possibleHit)==realTarget) // TODO: what if the real target is hidden behind >=2 layers of armor? it might random into another body part thats not armoring the real target
				{
					found=true;
				}
			}
		}

		for(possibleHit=storing.begin(); possibleHit!=storing.end();possibleHit++)
		{
			stabable.push_back(*possibleHit);

			if((*possibleHit)==realTarget) // TODO: what if the real target is hidden behind >=2 layers of armor? it might random into another body part thats not armoring the real target
			{
				found=true;
			}
		}

		if(found)
		{
			std::cout << " {" << realTarget->name(2) << " was internal stabbed!} ";
			realTarget->damage(0, 0, 0, stabHit, 0, 0, cause, villain, false, false, realTarget);
		}
		else if(!stabable.empty())
		{
			int hit=World::me->random(1, stabable.size());

			for(int i=0; hit>0;i++)
			{
				hit--;
				if(hit==0)
				{
					std::cout << " {" << stabable[i]->name(2) << " was internal stabbed!} ";
					stabable[i]->damage(0, 0, 0, stabHit, 0, 0, cause, villain, false, false, realTarget);
					break;
				}
			}
		}
		else
		{
			realBrokeHit+=stabHit/2;
		}
	}

	severHp+=slashHit;

	if(severHp>=maxHp)
	{
		std::cout << "{" << name(2) << " was sever severed!} ";

		if(attached.empty())
		{
			std::cout << "{but wasnt attached to anything, so was heavily injured instead!} ";

			maxHp-=std::max(10, (severHp/2));
			severHp=0;

			if(maxHp<=0 && initStatus!=2)
			{
				std::cout << " *SEVERBROKE " << name(2) << ", " <<brokeHp << "+" << severHp << "=" << brokeHp+severHp << "/" << maxHp << "* " << std::endl;
				World::me->remItem(this);
				return;
			}
		}
		else if(owner!=NULL)
		{
			severHp=0;
			owner->sever(this, true);
		}
		else
		{
			severHp=0;
			sever(NULL, true);
		}
	}

	if(cause!=NULL && canEmbed && (stabHit>0 || slashHit>0)) // TODO: minimum damage required?
	{
		if(cause->order==ITEM)
		{
			Item* obj=dynamic_cast<Item*>(cause);
			if(obj->embedders.count(this)==0)
			{
				embed(obj, true);
			}
		}
		// TODO: pushed into a spiked wall = impaled into it
	}

	if(impactHit>0)
	{
		int realImpactHit=impactHit;
		int preHp=impactHit;

		if(cause!=NULL && cause->order==ITEM)
		{
			// TODO: do we want impact limited by max hp? a penny could explode an armored at high speeds if not
//			Item* weapon=dynamic_cast<Item*>(cause);
//			realImpactHit=std::min(weapon->maxHp, realImpactHit);

			// TODO: any armor damages the weapon
		}

		std::cout << impactHit*World::forcePerDamage << " converted to " << preHp << " broke damage with " << World::me->forcePerDamage << " adjust, lowered by maxHp to " << realImpactHit << std::endl;

		realBrokeHit+=realImpactHit;

		if(!attached.empty() && realImpactHit+severHp>=maxHp) // If  we impact it enough, we sever it through sheer force and send it flying
		{
			if(attached.empty())
			{
				;
			}
			else if(owner!=NULL)
			{
				std::cout << " {" << name(2) << " was impact severed!} ";
				severHp=0;
				owner->sever(this, true);
			}
			else
			{
				std::cout << " {" << name(2) << " was impact severed!} ";
				severHp=0;
				sever(NULL, true);
			}

			if(realImpactHit*World::me->forcePerDamage>=1000)
			{
				std::cout << " {" << name(2) << " was impact gravitied!} ";
				this->addGravForce((realImpactHit*World::me->forcePerDamage/totalWeight()), cause, 0, villain);
			}
		}
		else if(owner!=NULL) // !bestOwners().empty() // TODO: if something held gets hit, aka a shield or a weapon we're holding or something, what happens?
		{
			owner->staggerHp+=realImpactHit;
			if(owner->staggerHp>200)
			{
				std::cout << " {" << owner->name(2) << " was stagger impact repelled!} ";
				owner->addGravForce((realImpactHit*World::me->forcePerDamage/owner->totalWeight()), cause, 0, villain);
			}
		}
		else if(realImpactHit*World::me->forcePerDamage>=1000)
		{
			std::cout << " {" << name(2) << " was force impact repelled!} ";
			this->addGravForce((realImpactHit*World::me->forcePerDamage/totalWeight()), cause, 0, villain);
		}
	}

	brokeHp=std::min(realBrokeHit+brokeHp, maxMaxHp);

	if(brokeHp>=maxHp)
	{
		maxHp-=brokeHit+maxHit;
	}
	else
	{
		maxHp-=(realBrokeHit>0 ? std::max(1, maxHit) : maxHit);
	}

	if(maxHp<=0 && initStatus!=2)
	{
		std::cout << " *BROKE " << name(2) << ", " <<brokeHp << "+" << severHp << "=" << brokeHp+severHp << "/" << maxHp << "* " << std::endl;
		World::me->remItem(this);
		return;
	}

	std::cout << " *" << (cause==NULL ? "? " : cause->name(0)) << "(" << (villain==NULL ? "?" : villain->name(0)) << ") " << " hit " << name(2) << ", " <<brokeHp << "+" << severHp << "=" << brokeHp+severHp << "/" << maxHp << "* ";
	std::cout << std::endl;
}


std::vector<Unit*> Item::bestOwners() {
	// Returns the unit/s that 'owns' this item the 'most':
	// If its an organ, returns only its owner
	// If its held by units and embedded in others, returns only the holders, not the embedded
	// Otherise, returns all holders / embedders

	std::vector<Unit*> ownList;

	if(owner!=NULL)
	{
		ownList.push_back(owner);
		return ownList;
	}

	// XXX: Can't just check for hiddeness, as dropping items and such checks here for if we're still connected to a unit at all
//	if(!isHidden)
//	{
//		return ownList;
//	}

	if(storer!=NULL)
	{
		return storer->bestOwners();
	}


	// XXX: if we consider people holding us as 'superior owners' to those subholding and / or holding embedded parts into us, add an early check here

	std::set<Unit*> checkedOwners;
	std::vector<Item*> ownedParts=getBlob(-1, 0, -3, 3, NULL, -1, 0); // get a list of everything holding / embedding / embedded into us

	for(unsigned int i=0;i<ownedParts.size();i++)
	{
		if(ownedParts[i]->owner!=NULL && checkedOwners.count(ownedParts[i]->owner)==0) // If it's owned, it's one of our weak owners
		{
				checkedOwners.insert(ownedParts[i]->owner);
				ownList.push_back(ownedParts[i]->owner);
		}
	}

	return ownList;
}

int Item::bestCarryLevel(Unit* checker) {
	// 0 = ground, 1 = stored or substored, 2 = held, embedded or carried at all, 3 = organ // TODO: -1 = stored in something on the ground?

	std::set<ItemCarryStatus> myList=allCarryStati(checker);

	if(myList.count(ORGAN)!=0)
	{
		return 3;
	}

	if(myList.count(STORED)!=0)
	{
		return 1;
	}

	if(myList.count(CARRIED)!=0)
	{
		return 2;
	}

	return 0;
}

std::set<ItemCarryStatus> Item::allCarryStati(Unit* checker) {
	std::set<ItemCarryStatus> myList;

	if(checker==NULL)
	{
		if(!isHidden) // TODO: always true?
		{
			myList.insert(GROUND);
		}
		else if(owner!=NULL)
		{
			myList.insert(ORGAN);
		}
		else if(!bestOwners().empty()) // In the case of something stored on the ground, it shouldn't count as "carried", right?
		{
			myList.insert(CARRIED);
		}

		if(!holders.empty())
		{
			myList.insert(HELD);
		}

		if(!embedders.empty())
		{
			myList.insert(EMBEDDED);
		}

		if(embedding!=NULL)
		{
			myList.insert(EMBEDDING);
		}

		if(storer!=NULL)
		{
			myList.insert(STORED);
		}
	}
	else
	{
		if(!isHidden) // TODO: always true?
		{
			return myList;
		}
		else if(owner==checker)
		{
			myList.insert(ORGAN);
		}
		else if(checker->connected(this, 1, 1, 1, 3)) // TODO: correct?
		{
			myList.insert(CARRIED);
		}

		if(!holders.empty())
		{
			std::set<Item*>::iterator next;
			for(next=holders.begin();next!=holders.end();next++)
			{
				if((*next)->owner==checker)
				{
					myList.insert(HELD);
					break;
				}
			}
		}

		if(!embedders.empty())
		{
			std::set<Item*>::iterator next;
			for(next=embedders.begin();next!=embedders.end();next++)
			{
				if((*next)->owner==checker)
				{
					myList.insert(EMBEDDED);
					break;
				}
			}
		}

		if(embedding!=NULL && embedding->owner==checker)
		{
			myList.insert(EMBEDDING);
		}

		if(storer!=NULL && (checker==NULL || World::me->vectorHas(storer->bestOwners(), checker)))
		{
			myList.insert(STORED);
		}
	}

	return myList;
}

int Item::strengthLevel(Unit* checker) {
	// How strong a grip we have on this item, or in the case its both an organ and being held by us, the greater value.

	if(checker==NULL)
	{
		return strength;
	}

	int curBest=0;
	std::set<Item*>::iterator next;

	if(owner==checker)
	{
		curBest=strength;

		for(next=attached.begin();next!=attached.end();next++) // TODO: correct? if we're attached to an arm / leg, we use its strength if better than ours
		{
			if((*next)->owner==checker)
			{
				curBest=std::max(curBest, (*next)->strength);
			}
		}
	}

	for(next=holders.begin();next!=holders.end();next++)
	{
		if((*next)->owner==checker)
		{
			curBest=std::max(curBest, (*next)->strength);
		}
	}

	return curBest;
}

int Item::totalWeight() {
	std::vector<Item*> myBlob=getBlob(1, 3, 1, 3, NULL, 0, 0);

	int total=0;
	for(unsigned int i=0;i<myBlob.size();i++)
	{
		total+=myBlob[i]->weight;
	}

	return total;
}


std::vector<Item*> Item::getBlob(int attachLevel, int storedLevel, int holdingLevel, int embedLevel, Unit* guy, int ownerLevel, int activeLevel) {
	// attachLevel: 0 = ignore INCLUDING THIS, 1 = search and include attached, -1 = search over attached parts but dont include
	// storedLevel: 0 = ignore, 1 = things we're storing, 2 = anything storing us, 3 = both, -1/2/3 = only things directly being stored / storing us
	// holdingLevel: 0 = ignore, 1 = anything we're holding, 2 = anything holding us, 3 = both, -1/2/3 = only the parts we're directly holding / being held by
	// embedLevel: 0 = ignore, 1 = we embed into only, 2 = embedded into us only, 3 = both, -1/2/3 = only those directly embedded / embedding
	// ownerLevel: 0 = ignore, 1 = only save if the part isn't our organ, 2 = only save our / neutral parts, 3 = only save enemy organs, -1/2/3 = don't expand if we succeed a check
	// 		4 = only expand / search if that part is one of ours / neutral, -4 = ignore and stop searching if we come across one of guy's parts
	// activeLevel: 0 = ignore, 1 = must be active, 2 = inactive usable (throw a broken gun), 3 = active usable (shoot a working gun), 4 = must be manipulable (type with a hand)


	// Owner examples:
	// -4 = expanding outward but ignoring a certain holder; if something we're holding can be thrown only if under a certain size, and we want the blob ignoring our holder

	if(activeLevel>1 && guy==NULL) // We need a unit to check if something is usable by X
	{
		std::cout << "getBlob item Long has activeLevel above 1, but no active checker?";
		World::me->pause();
	}
	// But we CAN use null for ownerLevels, though we should double check they're correctly used

	std::vector<Item*> currentBlob;

	std::queue<Item*> bodymaining; // Parts of our body to search through
	std::queue<Item*> remaining; // Other parts we're fully searching through
	std::queue<Item*> checkmaining; // Parts we're only checking and not expanding from
	std::set<Item*> checked;
	bodymaining.push(this);
	checked.insert(this);

	while(!bodymaining.empty() || !remaining.empty() || !checkmaining.empty())
	{
		Item* current=NULL;
		bool isBody=false;
		int checkLevel=0; // 0 = don't check this but expand the search, 1 = check this and expand the search too, 2 = only check this then stop

		if(!bodymaining.empty()) // AttachedLevel is only relevant to bodymaining, as anything else is either search completely (>0) or stop on the first instance (<0)
		{
			current=bodymaining.front();
			bodymaining.pop();

			isBody=true;

			if(attachLevel>0)
			{
				checkLevel=1;
			}
		}
		else if(!remaining.empty()) // Remaining always = other things than our attached blob
		{
			current=remaining.front();
			remaining.pop();

			checkLevel=1;
		}
		else if(!checkmaining.empty())
		{
			current=checkmaining.front();
			checkmaining.pop();

			checkLevel=2;
		}
		else
		{
			std::cout << "getBlob item Long has nothing left in either of its queues but is reached this line?";
			World::me->pause();
		}

		if(checkLevel>0) // If we're checking this thing
		{
			if(ownerLevel==4 || ownerLevel==-4)
			{
				if(ownerLevel==4 && current->owner!=NULL && current->owner!=guy) // 4 = only check / expand if that part is one of ours / neutral
				{
					continue;
				}
				else if(ownerLevel==-4 && current->owner==guy) // -4 = ignore and stop searching if we come across one of guy's parts
				{
					continue;
				}
			}

			if(activeLevel==0 ||
				(activeLevel==1 && current->isActive()) ||
				(activeLevel==2 && current->isUseable(guy)) ||
				(activeLevel==3 && current->isManipulatable(guy)))
			{
				if(ownerLevel==0 || ownerLevel==4 || ownerLevel==-4 ||
					((ownerLevel==1 || ownerLevel==-1) && current->owner!=guy) ||
					((ownerLevel==2 || ownerLevel==-2) && (current->owner==NULL || current->owner==guy)) ||
					((ownerLevel==3 || ownerLevel==-3) && current->owner!=NULL && current->owner!=guy))
				{

					currentBlob.push_back(current);

					if(ownerLevel<0)
					{
						continue;
					}
				}
			}

			if(checkLevel==2)
			{
//				// TODO: You're holding a backpack, and it has items inside it. Your actions should include grabbing those things right? and this is the way to do it?
//				// TODO: but say you're checking a backpack for an ammo clip, and you're check searching only the clip: it will now check the bullets = bad
//
//				std::set<Item*>::iterator next;
//				for(next=current->storing.begin();next!=current->storing.end();next++)
//				{
//					if(checked.count(*next)==0)
//					{
//						checkmaining.push(*next);
//						checked.insert(*next);
//					}
//				}

				continue;
			}
		}


		if(!isBody || attachLevel!=0) // We search attached parts of anything we reach at this point, but the body only if we're not 0 attachLevel
		{
			std::set<Item*>::iterator next;
			for(next=current->attached.begin();next!=current->attached.end();next++)
			{
				if(checked.count(*next)==0)
				{
					if(isBody)
					{
						bodymaining.push(*next);
					}
					else
					{
						remaining.push(*next);
					}
					checked.insert(*next);
				}
			}
		}

		if(storedLevel!=0 && storedLevel!=2 && storedLevel!=-2) // If storedLevel == 1, 3, -1 or -3, we check what we're storing
		{
			std::set<Item*>::iterator next;
			for(next=current->storing.begin();next!=current->storing.end();next++)
			{
				if(checked.count(*next)==0)
				{
					if(storedLevel<0)
					{
						checkmaining.push(*next);
					}
					else
					{
						remaining.push(*next);
					}
					checked.insert(*next);
				}
			}
		}

		if(storedLevel>=2 || storedLevel<=-2) // If storedLevel == 2, 3, -2 or -3, we check who's storing us
		{
			if(current->storer!=NULL && checked.count(current->storer)==0)
			{
				if(storedLevel<0) // TODO: this was :if(isBody), add to bodyMaining: before. why?
				{
					checkmaining.push(current->storer);
				}
				else
				{
					remaining.push(current->storer);
				}
				checked.insert(current->storer);
			}
		}

		if(holdingLevel!=0 && holdingLevel!=2 && holdingLevel!=-2) // If holdingLevel == 1, 3, -1 or -3, we check anything we're holding
		{
			if(current->holding!=NULL && checked.count(current->holding)==0)
			{
				checked.insert(current->holding);

				if(holdingLevel<0)
				{
					checkmaining.push(current->holding);
				}
				else // TODO: this was here and above: if(holdingLevel==-1 || (holdingLevel==-2 && (current->holding->bestCarryLevel(NULL)==2 || current->holding->owner==activeChecker)))
				{
					remaining.push(current->holding);
				}
			}
		}

		if(holdingLevel>=2 || holdingLevel<=-2) // If holdingLevel == 1, 3, -1 or -3, we check what's holding us
		{
			std::set<Item*>::iterator next;
			for(next=current->holders.begin();next!=current->holders.end();next++)
			{
				if(checked.count(*next)==0) // TODO: this was here: && (attachLevel==1 || !connected((*next), 0)))
				{
					checked.insert(*next);

					if(holdingLevel<0)
					{
						checkmaining.push(*next);
					}
					else
					{
						remaining.push(*next);
					}
				}
			}
		}

		if(embedLevel!=0 && embedLevel!=2 && embedLevel!=-2) // If embedLevel == 1, 3, -1 or -3, check things WE embed into
		{
			if(embedding!=NULL && checked.count(embedding)==0)
			{
				checked.insert(embedding);

				if(embedLevel<0)
				{
					checkmaining.push(embedding);
				}
				else
				{
					remaining.push(embedding);
				}
			}
		}

		if(embedLevel!=0 && embedLevel!=1 && embedLevel!=-1) // If holdingLevel == 2, 3, -2 or -3, check things embedded into us
		{
			std::set<Item*>::iterator next;
			for(next=current->embedders.begin();next!=current->embedders.end();next++)
			{
				if(checked.count(*next)==0)
				{
					checked.insert(*next);

					if(embedLevel<0)
					{
						checkmaining.push(*next);
					}
					else
					{
						remaining.push(*next);
					}
				}
			}
		}
	}

	return currentBlob;
}

std::vector<Item*> Item::attackableBlob() {
	std::vector<Item*> totalBlob=getBlob(1, 0, 0, 0, NULL, 0, 0); // TODO: correct? include held / embedded items?
	for(int i=totalBlob.size()-1;i>=0;i--)
	{
		if(totalBlob[i]->armor!=NULL && totalBlob[i]->storer==NULL)
		{
			totalBlob.erase(totalBlob.begin()+i);
		}
	}

	return totalBlob;
}

std::vector<Living*> Item::refreshBlob() {
	// Organs + Held + Held-blob + Stati + anyone else we're connected to via handholding

	std::vector<Living*> myBlob;

	if(myGrav!=NULL)
	{
		myBlob.push_back(myGrav);
	}

	std::queue<Item*> remaining;
	std::set<Living*> checked;
	remaining.push(this);
	checked.insert(this);
	while(!remaining.empty())
	{
		Item* current=remaining.front();
		remaining.pop();

		myBlob.push_back(current);

		for(unsigned int i=0;i<current->stati.size();i++)
		{
			myBlob.push_back(current->stati[i]);
		}

		std::set<Item*>::iterator next;
		for(next=current->attached.begin();next!=current->attached.end();next++)
		{
			if(checked.count(*next)==0)
			{
				remaining.push(*next);
				checked.insert(*next);
			}
		}

		for(next=current->storing.begin();next!=current->storing.end();next++)
		{
			if(checked.count(*next)==0)
			{
				remaining.push(*next);
				checked.insert(*next);
			}
		}

		if(current->storer!=NULL)
		{
			if(checked.count(current->storer)==0)
			{
				remaining.push(current->storer);
				checked.insert(current->storer);
			}
		}

		for(next=current->holders.begin();next!=current->holders.end();next++)
		{
			if(checked.count(*next)==0)
			{
				remaining.push(*next);
				checked.insert(*next);
			}
		}

		if(current->holding!=NULL)
		{
			if(checked.count(current->holding)==0)
			{
				remaining.push(current->holding);
				checked.insert(current->holding);
			}
		}

		if(current->myGrav!=NULL && checked.count(current->myGrav)==0)
		{
			myBlob.push_back(current->myGrav);
		}

		//TODO: also add in anything being stored, ie backpack or some shit
	}

	return myBlob;
}

bool Item::connected(Item* obj, int attachLevel, int storedLevel, int holdingLevel, int embedLevel) {
	// attachLevel: 0 = ignore, 1 = search, -1 = search but must not be attached
	// storedLevel: 0 = ignore, 1 = things we're storing, 2 = things storing us, 3 = both, -1/2/3 = only if we're directly storing/stored by them
	// holdingLevel: 0 = ignore, 1 = things we're holding, 2 = things holding us, 3 = both, -1/2/3 = only if we're directly holding/held by them
	// embedLevel: 0 = ignore, 1 = things we embed into, 2 = things embedded into us, 3 = both, -1/2/3 = only if we're directly embedding/embedded by them

	if(obj==this)
	{
		return true;
	}

	std::queue<Item*> remaining;
	std::set<Item*> checked;
	std::set<Item*> bodyparts;
	remaining.push(this);
	checked.insert(this);
	bodyparts.insert(this);

	while(!remaining.empty())
	{
		Item* current;

		current=remaining.front();
		remaining.pop();

		if(attachLevel!=0 || current!=this) // Attached to us check
		{
			std::set<Item*>::iterator next;
			for(next=current->attached.begin();next!=current->attached.end();next++)
			{
				if(checked.count(*next)==0)
				{
					if((*next)==obj)
					{
						return attachLevel>0;
					}

					remaining.push(*next);
					checked.insert(*next);

					if(bodyparts.count(current)!=0)
					{
						bodyparts.insert(*next);
					}
				}
			}
		}

		if(storedLevel==1 || storedLevel==3 || storedLevel==-1 || storedLevel==-3) // Things we're storing check
		{
			std::set<Item*>::iterator next;
			for(next=current->storing.begin();next!=current->storing.end();next++)
			{
				if(checked.count(*next)!=0)
				{
					continue;
				}
				else if(obj==(*next))
				{
					return true;
				}
				else if(storedLevel>0)
				{
					remaining.push(*next);
				}

				checked.insert(*next);
			}
		}

		if(storedLevel>=2 || storedLevel<=-2) // Thing storing us check
		{
			if(current->storer!=NULL && checked.count(current->storer)==0)
			{
				if(obj==current->storer)
				{
					return true;
				}
				else if(storedLevel>0)
				{
					remaining.push(current->storer);
				}

				checked.insert(current->storer);
			}
		}

		if(holdingLevel==1 || holdingLevel==3 || holdingLevel==-1 || holdingLevel==-3) // Things we're holding check
		{
			if(current->holding!=NULL && checked.count(current->holding)==0)
			{
				if(obj==current->holding)
				{
					return true;
				}
				else if(holdingLevel>0)
				{
					remaining.push(current->holding);
				}

				checked.insert(current->holding);
			}
		}

		if(holdingLevel>=2 || holdingLevel<=-2) // Things holding us check
		{
			std::set<Item*>::iterator next;
			for(next=current->holders.begin();next!=current->holders.end();next++)
			{
				if(checked.count(*next)!=0)
				{
					continue;
				}
				else if(obj==(*next))
				{
					return true;
				}
				else if(holdingLevel>0)
				{
					remaining.push(*next);
				}

				checked.insert(*next);
			}
		}

		if(embedLevel==1 || embedLevel==3 || embedLevel==-1 || embedLevel==-3) // Things we're embedded into check
		{
			if(current->embedding!=NULL && checked.count(current->embedding)==0)
			{
				if(obj==current->embedding)
				{
					return true;
				}
				else if(embedLevel>0)
				{
					remaining.push(current->embedding);
				}

				checked.insert(current->embedding);
			}
		}

		if(embedLevel>=2 || embedLevel<=-2) // Things embedded into us check
		{
			std::set<Item*>::iterator next;
			for(next=current->embedders.begin();next!=current->embedders.end();next++)
			{
				if(checked.count(*next)!=0)
				{
					continue;
				}
				else if(obj==(*next))
				{
					return true;
				}
				else if(embedLevel>0)
				{
					remaining.push(*next);
				}

				checked.insert(*next);
			}
		}
	}

	return false;
}


void Item::attach(Item* obj, bool isBrain, bool refreshNow) {
	// attach: obj is being attached to this. If this has inferior unitness, we'll swap positions shortly below
	// obj's type will automatically become whatever our carryStatus is, organ into organ or held into held etc

	if(obj==NULL)
	{
		std::cout << name(2) << " is trying to attach a null obj??";
		World::me->pause();
	}

	if(attached.count(obj)!=0)
	{
		std::cout << name(2) << " is trying to attach " << obj->name(2) << ", but they're already attached?";
		World::me->pause();
	}

	if(bestCarryLevel(NULL)<3 && isBrain)
	{
		std::cout << name(2) << " isnt an organ but is trying to attach " << obj->name(2) << " as a direct brain? we're not part of a unit dummy";
		World::me->pause();
	}




	int myUnitness=bestCarryLevel(NULL);
	int objUnitness=obj->bestCarryLevel(NULL);

	if(myUnitness==3 && objUnitness==3 && bestOwners().front()!=obj->bestOwners().front())
	{
		std::cout << name(2) << " is trying to attach a " << obj->name(2) << ", but my unitness is " << myUnitness << ", his is " << objUnitness<< ", and we have seperate owners?";
		World::me->pause();
	}

	if(objUnitness > myUnitness)
	{
		obj->attach(this, false, refreshNow);
		return;
	}

//	if(objUnitness==1)
//	{
//		std::cout << name(2) << " is trying to attach a " << obj->name(2) << ", but his unitness is " << objUnitness<< " while i'm stored, and we have seperate owners?";
//		World::me->pause();
//	}




	bool sameBody=connected(obj, 1, 0, 0, 0);
	bool sameBlob=connected(obj, 1, 3, 3, 3);

	if(sameBody && (myUnitness!=objUnitness))
	{
		std::cout << name(2) << " is trying to attach a " << obj->name(2) << ", but my unitness is " << myUnitness << ", his is " << objUnitness<< ", but we're preconnected already?";
		World::me->pause();
	}

	if(obj->xPos!=xPos || obj->yPos!=yPos || obj->zPos!=zPos)
	{
		World::me->moveItem(obj, obj->xPos, obj->yPos, obj->zPos);
	}

	// Both must be of the same owner 						TODO: change this? just make current owner drop it? probably necessary



	//Me Obj	Possible?		sameBody?		sameBlob?		Examples TODO: check below for storage / armor															Seperate blob version
	// 0 0		Yes			-	   Maybe	-      Maybe	-	A chain of rocks connecting at its two ends 												///// Two seperate rocks connecting
	// 0 1				No											XXX: Would have attached the other way
	// 0 2		        No											XXX: Would have attached the other way
	// 0 3		        No											XXX: Would have attached the other way
	// 0 4		        No											XXX: Would have attached the other way
	// 1 0		Yes			-			No	-			No	-	A stored magnet attraching a piece of iron from the ground
	// 1 1		Yes			-		Maybe	-		Maybe	-	A stored gemstone fusing with another stored gemstone
	// 1 2				No
	// 1 3				No
	// 1 4				No
	// 2 0		Yes			-	        No	-	        No	-	A crafter connecting a sharp rock to a stick he's holding
	// 2 1				No
	// 2 2		Yes			-	   Maybe	-	   Maybe	-	A crafter connecting two seperate sticks ///// A crafter connecting two ends of a chain of sticks ///// Two crafters connecting two sticks they're each holding
	// 2 3		        No											XXX: Would have attached the other way
	// 2 4		        No											XXX: Would have attached the other way
	// 3 0		Yes			-			No	-			No	-	A breastplate attaching a tracker from the ground
	// 3 1				No
	// 3 2		Yes			-	  		No	-	   Maybe	-	A breastplate attaching a tracker held by its owner					 ///// A breastplate attaching a tracker held by an enemy
	// 3 3		Yes			-		Maybe	-	Yes			-	A breastplate attaching another end of a chain already connected to it
	// 3 4				No											XXX: Would have attached the other way
	// 4 0		Yes			-	        No	-	        No	-	A blob attaching a random limb they found on the ground
	// 4 1				No
	// 4 2		Yes			-	        No  -      Maybe	-	A robot reattaching a severed arm he's holding 							///// A robot attaching a severed arm to another robot
	// 4 3		Yes			-			No	-	Yes				A chest fusing with its organic fleshplate cover
	// 4 4		Yes			-	Yes			-	Yes			-	A living spiderweb reconnecting limbs to form a circle

	if(objUnitness==1 && (myUnitness>1 || (myUnitness==1 && storer!=obj->storer))) // If obj is being stored away from us, unstore it so it can legally attach to whatever we are
	{
		obj->storer->unstore(obj, false);
	}

	if(!sameBlob) // If two seperate blobs, handle gravity
	{
		// Case: Two robots holding 2 sticks attaching together: neither of them should have their gravs removed or transfered, right?
		// Actually: in cases like that, if gravity was on one of them they shouldn't be holding things and shouldn't be able to attach things to eachother, so that case doesnt happen
		// The only case I can think of where we'd have gravity and attach something would be something auto regening limbs mid-flight, which is safe to force gravity sharing with

		// Actually, case 2: some poor sucker is flying by and we impale him, embedding our spear while we still hold it, which would transfer his gravity to us
		// that means TODO: being impaled means we should remove gravity from the target?



		if(obj->myGrav!=NULL) // Always get rid of obj's gravity
		{
			// Remove the gravity, not just disown on their blob:
			//	if its ground, get rid of the grav who cares
			//	if its something held and not with us, they shouldnt have a gravity because grav-effected people can't hold things,
			//  it wouldn't be an organ cuz it has to be attached to us at this point, otherwise we'd have less unitness and be attaching to it

			World::me->remGravity(obj->myGrav);
		}

		if(myGrav!=NULL) // Always transfer our gravity onto its blob
		{
			myGrav->claim(obj);
		}
	}


	if(!sameBody)
	{
		if(myUnitness>1) // If we're owned by a unit that doesn't know about obj, or if we're an organ/armor and obj isn't, make owner soft / hard claim the parts
		{
			if(owner!=NULL) // If we're this guy's organ and obj isnt yet, attach it to our true owner
			{
				owner->attach(obj, isBrain);
			}

			owner->tryClaim(obj, false); // let them try to claim it. If they already have, who cares
		}
	}

	// TODO: Below = drop eachother if held, but do we want this to happen automatically? attached can still hold eachother
	if(obj->holding==this)
	{
		obj->holding=NULL;
		holders.erase(obj);
	}

	if(obj->embedding==this)
	{
		dislodge(obj, false);
	}

	if(embedding==obj)
	{
		obj->dislodge(this, false);
	}

	if(holding==obj)
	{
		holding=NULL;
		obj->holders.erase(this);
	}

	if(myUnitness==1)
	{
		storer->store(obj, false);
	}

	attached.insert(obj);
	obj->attached.insert(this);


	World::me->addRefresher(this, refreshNow);
}

void Item::sever(Item* obj, bool refreshNow) {
	// obj is being cut off of this. Only means this keeps the current gravity and limb gets a copied gravity

	if(attached.empty())
	{
		std::cout << "item " << name(2) << " trying to sever from a " << obj->name(2) << ", but it doesn't have any attached parts?";
		World::me->pause();
		return;
	}

	if(obj==NULL)
	{
		sever(*(attached.begin()), refreshNow);
		return;
	}

	if(attached.count(obj)==0)
	{
		std::cout << "item " << name(2) << " trying to sever from " << obj->name(2) << ", but the two aren't directly connected? ";
		if(connected(obj, 1, 3, 3, 3))
		{
			std::cout << " They are connected somewhere tho";
		}
		World::me->pause();
		return;
	}

	if(bestCarryLevel(NULL)!=obj->bestCarryLevel(NULL))
	{
		std::cout << "item " << name(2) << " trying to sever from " << obj->name(2) << ", but we have different carry statuses?";
		World::me->pause();
	}


	std::cout << "(" << name(2) << " is severing " << obj->name(2)  << ") " ;

	if(obj->armor==this)
	{
		obj->armorsever(false);
	}
	else if(armor==obj)
	{
		armorsever(false);
	}

	obj->attached.erase(this);
	attached.erase(obj);


	if(connected(obj, 1, 0, 0, 0))// SHOULD be attached only: you hold 2 ends of a wire, some enemy holds one end, you cut down the middle = same blob but one side no longer claimed by enemy
	{
		World::me->addRefresher(this, refreshNow);
		return;
	}

	bool lostGrav=(!connected(obj, 1, 3, 3, 3) && myGrav!=NULL);

	if(owner!=NULL)
	{
		if(!owner->connected(this, 1, 0, 0, 0))
		{
			owner->detach(this, false);
		}
		else if(!owner->connected(obj, 1, 0, 0, 0)) // TODO: used to be (obj->bestCarryLevel(owner)!=3)
		{
			owner->detach(obj, false);
		}
	}

	disowned(false);
	obj->disowned(false);


	if(lostGrav) // If we have gravity and they're fully seperated, give limb a copy and make sure to disown the owner as well
	{
		if(obj->owner!=NULL) // Not that it really matters, but we prefer to keep gravity on the one that's still an organ
		{
			obj->myGrav->disown(this);
			obj->myGrav->copy(this);
		}
		else
		{
			myGrav->disown(obj);
			myGrav->copy(obj);
		}
	}


	if(!connected(obj, 1, 3, 3, 3)) // If we're seperated from limb, copy over stati effects from both sides if applicable
	{
		std::vector<Item*> limbBlob=obj->getBlob(1, 2, 3, 3, NULL, 0, 0);
		for(unsigned int i=0;i<limbBlob.size();i++)
		{
			std::vector<Status*> afflictions(limbBlob[i]->stati);
			for(unsigned int i=0;i<afflictions.size();i++)
			{
				afflictions[i]->disown(this);
			}
		}

		std::vector<Item*> thisBlob=getBlob(1, 2, 3, 3, NULL, 0, 0);
		for(unsigned int i=0;i<thisBlob.size();i++)
		{
			std::vector<Status*> afflictions(thisBlob[i]->stati);
			for(unsigned int i=0;i<afflictions.size();i++)
			{
				afflictions[i]->disown(obj);
			}
		}
	}

	World::me->addRefresher(obj, false);
	World::me->addRefresher(this, refreshNow);
}

void Item::disowned(bool refreshNow) {
	// disowned = at least one unit has forsaken us, and we lower ourselves to whatever / wherever we should be now

	int newStatus=bestCarryLevel(NULL);

	if(newStatus==3)
	{
		return;
	}

	std::vector<Item*> myBlob=getBlob(1, 0, 0, 3, NULL, 0, 0);

	for(unsigned int i=0;i<myBlob.size();i++)
	{
		if(myBlob[i]->holding!=NULL && myBlob[i]->owner==NULL) // If something is embedded into us / us into it, they might be an organ carrying something, so double check here
		{
			myBlob[i]->drop(false);
		}

		if(newStatus==0) // If we have no more owners, make us drop to the ground. If we're dieing and this is being done from World::remItem, then it will skip it there
		{
			World::me->unhideItem(myBlob[i]);
		}
		else // Else, check that our new primary owner recieves us item in its square
		{
			Unit* newOwner=bestOwners().front();
			if(myBlob[i]->xPos!=newOwner->xPos || myBlob[i]->yPos!=newOwner->yPos || myBlob[i]->zPos!=newOwner->zPos)
			{
				std::cout << "[" << myBlob[i]->name(2) << " is being disown moved to new bestowner " << newOwner->name(2) << "!] ";
				World::me->moveItem(myBlob[i], newOwner->xPos, newOwner->yPos, newOwner->zPos);
			}
		}
	}

	World::me->addRefresher(this, refreshNow);
}

void Item::armortach(Item* obj, bool refreshNow) {
	// obj is becoming the armor of this

	if(obj==NULL)
	{
		std::cout << name(2) << " was told to armortach a null obj?";
		World::me->pause();
	}

	if(obj->attached.count(this)==0)
	{
		attach(obj, false, false);
	}

	armor=obj;

	World::me->addRefresher(this, refreshNow);
}

void Item::armorsever(bool refreshNow) {
	// this is dropping whatever armor it has
	// though sever will also remove whatever armor we have

	if(armor==NULL)
	{
		std::cout << name(2) << " was told to armorsever with no armor?";
		World::me->pause();
	}

	armor=NULL;

	World::me->addRefresher(this, refreshNow);
}

void Item::grab(Item* obj, bool refreshNow) {
	// obj is being grabbed by this

	if(obj==NULL)
	{
		std::cout << name(2) << " was told to grab a null obj?";
		World::me->pause();
	}

	if(attached.count(obj)!=0)
	{
		std::cout << name(2) << " was told to grab " << obj->name(2) << ", but they're attached?";
		World::me->pause();
	}

	if(owner==NULL)
	{
		std::cout << name(2) << " was told to grab " << obj->name(2)  << ", but its not an organ so how is it grabbing?" ;
		World::me->pause();
	}

	if(holding!=NULL)
	{
		std::cout << name(2) << " was told to grab " << obj->name(2)  << ", but i'm already holding a " << holding->name(2) ;
		World::me->pause();
	}

	if(obj->storer!=NULL)
	{
		obj->storer->unstore(obj, false);
	}

	if(obj->myGrav!=NULL && myGrav!=obj->myGrav) // If we're catching something we remove its gravity, but we should take care if we're grabbing part of us
	{
		obj->myGrav->disown(obj);
	}
//	else if( obj->is a block)	TODO: grab onto edge walls to slow / stop our fall
//	{
//		remove our grav
//	}

	owner->tryClaim(obj, false);

	holding=obj;
	obj->holders.insert(this);

	World::me->addRefresher(this, refreshNow);
}

void Item::drop(bool refreshNow) {
	// THIS is dropping anything its holding

	if(holding==NULL)
	{
		std::cout << name(2) << " was told to drop but we aint holding anything?";
		World::me->pause();
	}

//	if(bestCarryStatus()<3)      If this is on, when we sever it drop is called AFTER we sever so its not an organ at this point
//	{
//		std::cout << name(2) << " was told to drop " << obj->name(2)  << ", but its not an organ so how is it grabbing?" ;
//		World::me->pause();
//	}

	if(holding->holders.count(this)==0)
	{
		std::cout << name(2) << " was told to drop " << holding->name(2)  << ", but obj doesn't think i'm holding it? " ;
		World::me->pause();
	}

	std::cout << " (" << name(2) << " is dropping " << holding->name(2) << " ) " ;

	Item* obj=holding;
	holding->holders.erase(this);
	holding=NULL;

	obj->disowned(false);

	World::me->addRefresher(obj, false);
	World::me->addRefresher(this, refreshNow);
}

void Item::fullDrop(bool refreshNow) {
	// We release ourselves from all holders, but still hold onto things ourselves

	std::vector<Item*> holders=getBlob(-1, 0, -2, 3, NULL, -1, 0); // TODO: including our embedded parts, correct?
	for(unsigned int i=0;i<holders.size();i++)
	{
		holders[i]->drop(refreshNow);
	}

	if(!getBlob(-1, 0, -2, 3, NULL, -1, 0).empty())
	{
		std::cout << name(2) << " was told to fulldrop but we still have holders afterwards?";
		World::me->pause();
	}

	if(bestCarryLevel(NULL)==2)
	{
		std::cout << name(2) << " was told to fulldrop but we're still counted as held afterwards?";
		World::me->pause();
	}
}

void Item::store(Item* obj, bool refreshNow) {
	// Obj is being stored in this

	// TODO: canStore, to check if we have storage space / obj is only being held by one guy / etc

	if(obj==NULL) // Can't store null
	{
		std::cout << name(2) << " was told to store a null obj?";
		World::me->pause();
	}

	if(attached.count(obj)!=0) // Can't store attached parts
	{
		std::cout << name(2) << " was told to store " << obj->name(2) << ", but they're attached?";
		World::me->pause();
	}

	if(connected(obj, 1, 0, 0, 3)) // Can't store parts of the same blob
	{
		std::cout << name(2) << " was told to store " << obj->name(2) << ", but they're part of the same 0 blob?";
		World::me->pause();
	}

	if(storer!=NULL) // Can't store things already being stored
	{
		// TODO: not really a problem, but for now it shouldnt happen in testing
		std::cout << name(2) << " was told to store " << obj->name(2)  << ", but we're already being stored?" ;
		World::me->pause();
	}

	// TODO: if being held, drop it automatically? if not, change the 3 below to 2 to check for this

	if(obj->bestCarryLevel(NULL)==3) // Can't store organs
	{
		// TODO: but we should be able to in the future: collection of talking heads
		std::cout << name(2) << " was told to store " << obj->name(2)  << ", but obj is an organ?" ;
		World::me->pause();
	}

	if(obj->bestCarryLevel(NULL)!=2 && obj->initStatus!=0) // Things about to be stored should be being held, or being init
	{
		// TODO: not really a problem, but shouldn't happen yet
		std::cout << name(2) << " was told to store " << obj->name(2)  << ", but obj isn't being held? not a problem later, but shouldnt happen yet" ;
		World::me->pause();
	}

	std::vector<Item*> objBlob=obj->getBlob(1, 0, 0, 3, NULL, 0, 0);

	for(unsigned int i=0;i<objBlob.size();i++)
	{
		if(objBlob[i]->bestCarryLevel(NULL)==3)
		{
			std::cout << name(2) << " was told to store " << obj->name(2)  << ", but part of its blob is organ?" << objBlob[i];
			World::me->pause();
		}

		while(!objBlob[i]->holders.empty())
		{
			(*objBlob[i]->holders.begin())->drop(objBlob[i]);
		}
	}

	std::vector<Unit*> owners=bestOwners();
	if(!owners.empty())
	{
		owners[0]->tryClaim(obj, false);
	}

	for(unsigned int i=0;i<objBlob.size();i++)
	{
		objBlob[i]->storer=this;
		storing.insert(objBlob[i]);
	}

	World::me->addRefresher(this, refreshNow);
}

void Item::unstore(Item* obj, bool refreshNow) {
	// This is removing obj from its stored area
	// For grabbing, the grab happens BEFORE we unstore so it's still connected to something. For item death unstoring, we gotta make sure they all drop out manually

	if(obj==NULL)
	{
		std::cout << name(2) << " was told to unstore a null obj?";
		World::me->pause();
	}

	if(attached.count(obj)!=0)
	{
		std::cout << name(2) << " was told to unstore " << obj->name(2) << ", but they're attached which shouldn't have happened before?";
		World::me->pause();
	}

	if(storing.count(obj)==0)
	{
		std::cout << name(2) << " was told to unstore " << obj->name(2)  << ", but it says I'm not holding anything?" ;
		World::me->pause();
	}

	if(obj->storer==NULL)
	{
		std::cout << name(2) << " was told to unstore " << obj->name(2)  << ", but obj doesn't think i'm holding it? " ;
		World::me->pause();
	}

	if(obj->storer!=this)
	{
		std::cout << name(2) << " was told to unstore " << obj->name(2)  << ", but obj thinks " << obj->storer->name(2) << " is holding it? " ;
		World::me->pause();
	}

	if(obj->allCarryStati(NULL).count(STORED)==0)
	{
		std::cout << name(2) << " was told to unstore " << obj->name(2)  << ", but obj isnt stored type?";
		World::me->pause();
	}

	std::vector<Item*> objBlob=obj->getBlob(1, 0, 0, 3, NULL, 0, 0); // Everything attached / embedded / embedding into us

	for(unsigned int i=0;i<objBlob.size();i++)
	{
		if(storing.count(objBlob[i])==0)
		{
			std::cout << name(2) << " was told to unstore " << obj->name(2)  << ", but it says I'm not holding one of its blob parts?" << objBlob[i]->name(2) ;
			World::me->pause();
		}

		objBlob[i]->storer=NULL;
		storing.erase(objBlob[i]);
	}

	obj->disowned(false);

	World::me->addRefresher(obj, false);
	World::me->addRefresher(this, refreshNow);
}

void Item::embed(Item* obj, bool refreshNow) {
	// Obj is being embedded into this

	if(obj==NULL)
	{
		std::cout << name(2) << " was told to embed a null obj?";
		World::me->pause();
	}

	if(storer!=NULL)
	{
		// not really a problem, but for now it shouldnt happen in testing
		std::cout << name(2) << " was told to embed " << obj->name(2)  << ", but we're being stored?" ;
		World::me->pause();
	}

	if(obj->storer!=NULL)
	{
		// not really a problem, but for now it shouldnt happen in testing
		std::cout << name(2) << " was told to embed " << obj->name(2)  << ", but they're being stored?" ;
		World::me->pause();
	}


	if(bestCarryLevel(NULL)!=0) // If we have an owner, try and claim obj no matter where it is
	{
		bestOwners().front()->tryClaim(obj, false);
	}

	if(obj->myGrav!=NULL && obj->myGrav!=myGrav) // If obj has any gravity, it should be handled when the object collides with us, not here
	{
		World::me->remGravity(obj->myGrav);
	}

	if(storer!=NULL)
	{
		storer->store(obj, false);
	}

	obj->embedding=this;
	embedders.insert(obj);

	World::me->addRefresher(this, refreshNow);
}

void Item::dislodge(Item* obj, bool refreshNow) {
	// This is removing obj from its list of embedded objects

	if(obj==NULL)
	{
		std::cout << name(2) << " was told to dislodge a null obj?";
		World::me->pause();
	}

	if(embedders.count(obj)==0)
	{
		std::cout << name(2) << " was told to dislodge " << obj->name(2)  << ", but it says I'm not embedded at all?" ;
		World::me->pause();
	}

	if(obj->embedding==NULL)
	{
		std::cout << name(2) << " was told to dislodge " << obj->name(2)  << ", but obj doesn't think its embedding at all? " ;
		World::me->pause();
	}

	if(obj->embedding!=this)
	{
		std::cout << name(2) << " was told to unstore " << obj->name(2)  << ", but obj thinks " << obj->storer->name(2) << " is holding it? " ;
		World::me->pause();
	}

	obj->embedding=NULL;
	embedders.erase(obj);

	disowned(false);
	obj->disowned(false);

	World::me->addRefresher(obj, false);
	World::me->addRefresher(this, refreshNow);
}


int Item::count(std::string name, ItemTag tagType, int attachLevel, int storedLevel, int holdingLevel, int embedLevel, Unit* guy, int ownerLevel, int activeLevel) {
	return getParts(name, tagType, attachLevel, storedLevel, holdingLevel, embedLevel, guy, ownerLevel, activeLevel).size();
}

Item* Item::getPart(std::string name, ItemTag tagType, int attachLevel, int storedLevel, int holdingLevel, int embedLevel, Unit* guy, int ownerLevel, int activeLevel) {
	std::vector<Item*> myBlob=getBlob(attachLevel, storedLevel, holdingLevel, embedLevel, guy, ownerLevel, activeLevel);

	for(unsigned int i=0;i<myBlob.size();i++)
	{
		if((name=="" || myBlob[i]->species==name) &&
			(tagType==NULL_ITEM_TAG || myBlob[i]->selfTags.count(tagType)!=0))
		{
			return myBlob[i];
		}
	}

	return NULL;
}

std::vector<Item*> Item::getParts(std::string name, ItemTag tagType, int attachLevel, int storedLevel, int holdingLevel, int embedLevel, Unit* guy, int ownerLevel, int activeLevel) {
	std::vector<Item*> results;

	std::vector<Item*> myBlob=getBlob(attachLevel,  storedLevel, holdingLevel, embedLevel, guy, ownerLevel, activeLevel);
	for(unsigned int i=0;i<myBlob.size();i++)
	{
		if((name=="" || myBlob[i]->species==name) &&
			(tagType==NULL_ITEM_TAG || myBlob[i]->selfTags.count(tagType)!=0))
		{
			results.push_back(myBlob[i]);
		}
	}

	return results;
}


void Item::fullRefresh() {
	std::vector<Unit*> owners=bestOwners();
	if(!owners.empty())
	{
		owners.front()->fullRefresh();
		return;
	}

	retag(NULL);

	std::vector<Living*> myBlob=refreshBlob();
	for(unsigned int i=0;i<myBlob.size();i++)
	{
		if(!myBlob[i]->refresh())
		{
			fullRefresh();
			return;
		}
	}
}

bool Item::refresh() {
	if(bestOwners().empty() && myGrav==NULL && fallCheck() && initStatus!=2)
	{
		if(isHidden)
		{
			std::cout << name(2) << " is hidden, but is starting to fall? ";
			World::me->pause();
		}

		std::cout << "(" << name(2) << " started to itemfall!) ";
		World::me->addGravity(new Gravity(this));
		return false;
	}
	return true;
}

bool Item::isActive() {
	// if the item is active in general

	return brokeHp<maxMaxHp/2;
}

bool Item::isUseable(Unit* user) {
	// If the unit is capable of 'using' said item, even if it doesn't belong to them. AKA: can we swing this sword
	// Usable doesn't neccesarily mean "useable": if you're holding a gun this will return true, but it may be broken to the point it can't fire which should be a separate isActive check

	if(user==NULL)
	{
		return false;
	}

	int claimLevel=bestCarryLevel(user);

	if(claimLevel==3)
	{
		std::set<Item*>::iterator next;	// If someone is holding our sword arm, we can't use it like normal
		for(next=holders.begin();next!=holders.end();next++)
		{
			if((*next)->owner!=user) // TODO: does this work?
			{
				return false;
			}
		}

		return true;
	}
	else if(claimLevel==2)
	{
		if(owner!=NULL) // It's being held by us, but is someone else's body part
		{
			return false;
		}

		if(holders.empty()) // It's being subheld by us, and isn't what we're directly holding
		{
			return false;
		}

		if(!getBlob(-1, 0, -1, 3, user, 3, 0).empty()) // If any part of a held blob is held by someone else, we can't use it
		{
			return false;
		}


		return true; // If it has a holder and nobody else is holding it, we're holding it
	}

	return false;
}

bool Item::isManipulatable(Unit* user) {
	// if this item is something the user can manipulate with direct control, like using their hand to type on a keyboard

	if(!isActive())
	{
		return false;
	}

	return owner==user;
}

void Item::retag(std::multiset<Tag>* sharedTags) {
	if(!bestOwners().empty() && sharedTags==NULL)
	{
		std::cout << "Why is an item retagging from null when it has owners? " << name(2) << " " << bestOwners()[0]->name(2) << std::endl;
		World::me->pause();
		bestOwners()[0]->retag(NULL);
		return;
	}

	std::multiset<Tag> extraTags;
	std::vector<Living*> myBlob=refreshBlob();
	if(sharedTags==NULL)
	{
		for(unsigned int i=0;i<myBlob.size();i++)
		{
			if(myBlob[i]->order==STATUS)
			{
				Status* effect=dynamic_cast<Status*>(myBlob[i]);
				extraTags.insert(effect->duoTags.begin(), effect->duoTags.end());
			}
			else if(myBlob[i]->order==ITEM)
			{
				Item* obj=dynamic_cast<Item*>(myBlob[i]);
				extraTags.insert(obj->duoTags.begin(), obj->duoTags.end());
			}
		}
	}
	else
	{
		extraTags=*sharedTags;
	}



	tags.clear();
	tags.insert(soloTags.begin(), soloTags.end());

	std::vector<Status*> afflictions(stati);
	for(unsigned int i=0;i<afflictions.size();i++)
	{
		tags.insert(afflictions[i]->soloTags.begin(), afflictions[i]->soloTags.end());
	}

	tags.insert(extraTags.begin(), extraTags.end());

	if(sharedTags==NULL)
	{
		for(unsigned int i=0;i<myBlob.size();i++)
		{
			if(myBlob[i]->order==ITEM)
			{
				Item* obj=dynamic_cast<Item*>(myBlob[i]);
				obj->retag(&extraTags);
			}
		}
	}
}


void Item::tryDie() {
	if(owner!=NULL && !owner->letDie(this))
	{
		return;
	}

	for(unsigned int i=0; i<stati.size(); i++)
	{
		if(stati[i]->letDie(this))
		{
			return;
		}
	}

	std::cout << "[" << name(2) << " was killed!] ";
	World::me->remItem(this);
}


std::string Item::name(int detail) {
	// 0 = just species + id, 1 = + location, 2 = + info on owner / carrystatus

	if(detail==0)
	{
		return species + " " + std::to_string(id);
	}
	else if(detail==1)
	{

		return species + " " + std::to_string(id) + " (" + std::to_string(xPos) + " " + std::to_string(yPos) + ")";
	}
	else
	{
//		std::cout << std::endl;
//		std::cout << (bestOwner()==NULL ? "None" : bestOwner()->name(0));
//		std::cout << std::endl;
//		std::cout << std::to_string(bestCarryStatus());
//		std::cout << std::endl;
//		std::cout << species + " " + std::to_string(id) + " (" + std::to_string(xPos) + " " + std::to_string(yPos) + ") {" +
//				((bestOwner()==NULL ? "None" : bestOwner()->name(0))+ " : " + std::to_string(bestCarryStatus()))
//				+ "} ";
//		std::cout << std::endl;
		return species + " " + std::to_string(id) + " (" + std::to_string(xPos) + " " + std::to_string(yPos) + ") {" +
				((bestOwners().empty() ? "None" : bestOwners()[0]->name(0))+ " : " + std::to_string(bestCarryLevel(NULL)))
				+ "} ";

	}
}
