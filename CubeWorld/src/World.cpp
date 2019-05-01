
#include "World.h"

#include "SquareQueue.h"
#include "Entities/Blocks/Natural/Empty.h"
#include "Entities/Blocks/Natural/Nogo.h"
#include "Entities/Blocks/Natural/Grass.h"
#include "Entities/Blocks/Natural/CutRock.h"

#include "Entities/Units/Basic Bots/DrunkBot.h"
#include "Entities/Units/Basic Bots/SkeletonBot.h"
#include "Entities/Units/Basic Bots/HelloBot.h"
#include "Entities/Units/Basic Bots/FrogBot.h"
#include "Entities/Units/Basic Bots/BoxerBot.h"
#include "Entities/Units/Basic Bots/MagicianBot.h"
#include "Entities/Units/Basic Bots/WalkerBot.h"
#include "Entities/Units/Basic Bots/ZombieBot.h"
#include "Entities/Units/Basic Bots/SlasherBot.h"
#include "Entities/Units/Basic Bots/ArmorBot.h"
#include "Entities/Units/Basic Bots/StabberBot.h"
#include "Entities/Units/Basic Bots/PickupBot.h"
#include "Entities/Units/Basic Bots/KidnapperBot.h"
#include "Entities/Units/Basic Bots/ThrowBot.h"
#include "Entities/Units/Basic Bots/CowboyBot.h"


#include <math.h>
#include <float.h>

#include "windows.h"

World::World(int x, int y, int z, std::string* preset, int time, int totalLanes) {
	xMax=x;
	yMax=y;
	zMax=z;

	std::cout.precision(4);

	delay=time;
	numLanes=totalLanes;
	curId=1;

	me=this;

	cube=new Square***[x];
	for(int i=0;i<x;i++)
	{
		cube[i]=new Square**[y];

		for(int j=0;j<y;j++)
		{
			cube[i][j]=new Square*[z];

			for(int k=0;k<z;k++)
			{
				cube[i][j][k]=new Square(i,j,k);
			}
		}
	}

	for(int i=0;i<xMax;i++)
	{
		for(int j=0;j<yMax;j++)
		{
			for(int k=0;k<zMax;k++)
			{
				if(i==0 || i==xMax-1 || j==0 || j==yMax-1 || k==0 || k==zMax-1)
				{
					addBlock(new Nogo(i, j, k));
				}
				else
				{
					addBlock(new Empty(i, j, k));
				}
			}
		}
	}

	for(int i=1;i<x-1;i++)
	{
		for(int j=1;j<y-1;j++)
		{
			char here=preset[y-2-j].at(i-1);

			if(here==' ')
			{
				;
			}
			else if(here=='1')
			{
				World::me->addBlock(new Grass(i, j, 1));
			}
			else if(here=='2')
			{
				World::me->addBlock(new Grass(i, j, 1));
				World::me->addBlock(new Grass(i, j, 2));
			}
			else if(here=='3')
			{
				World::me->addBlock(new Grass(i, j, 1));
				World::me->addBlock(new Grass(i, j, 2));
				World::me->addBlock(new Grass(i, j, 3));
			}
			else if(here=='4')
			{
				World::me->addBlock(new Grass(i, j, 1));
				World::me->addBlock(new Grass(i, j, 2));
				World::me->addBlock(new Grass(i, j, 3));
				World::me->addBlock(new Grass(i, j, 4));
			}
			else if(here=='5')
			{
				World::me->addBlock(new Grass(i, j, 1));
				World::me->addBlock(new Grass(i, j, 2));
				World::me->addBlock(new Grass(i, j, 3));
				World::me->addBlock(new Grass(i, j, 4));
				World::me->addBlock(new Grass(i, j, 5));
			}
			else if(here=='6')
			{
				World::me->addBlock(new CutRock(i, j, 1));
			}
			else if(here=='7')
			{
				World::me->addBlock(new CutRock(i, j, 1));
				World::me->addBlock(new CutRock(i, j, 2));
			}
			else if(here=='8')
			{
				World::me->addBlock(new CutRock(i, j, 1));
				World::me->addBlock(new CutRock(i, j, 2));
				World::me->addBlock(new CutRock(i, j, 3));
			}
			else if(here=='9')
			{
				World::me->addBlock(new CutRock(i, j, 1));
				World::me->addBlock(new CutRock(i, j, 2));
				World::me->addBlock(new CutRock(i, j, 3));
				World::me->addBlock(new CutRock(i, j, 4));
			}
			else if(here=='w')
			{
				World::addUnit(new WalkerBot(i, j, 1));
			}
			else if(here=='d')
			{
				World::addUnit(new DrunkBot(i, j, 1));
			}
			else if(here=='s')
			{
				World::addUnit(new SkeletonBot(i, j, 1));
			}
			else if(here=='h')
			{
				World::addUnit(new HelloBot(i, j, 1));
			}
			else if(here=='f')
			{
				World::addUnit(new FrogBot(i, j, 1));
			}
			else if(here=='b')
			{
				World::addUnit(new BoxerBot(i, j, 1));
			}
			else if(here=='M')
			{
				World::addUnit(new MagicianBot(i, j, 1));
			}
			else if(here=='z')
			{
				World::addUnit(new ZombieBot(i, j, 1));
			}
			else if(here=='S')
			{
				World::addUnit(new SlasherBot(i, j, 1));
			}
			else if(here=='A')
			{
				World::addUnit(new ArmorBot(i, j, 1));
			}
			else if(here=='T')
			{
				World::addUnit(new StabberBot(i, j, 1));
			}
			else if(here=='p')
			{
				World::addUnit(new PickupBot(i, j, 1));
			}
			else if(here=='k')
			{
				World::addUnit(new KidnapperBot(i, j, 1));
			}
			else if(here=='t')
			{
				World::addUnit(new ThrowBot(i, j, 1));
			}
			else if(here=='C')
			{
				World::addUnit(new CowboyBot(i, j, 1));
			}
			else
			{
				std::cout << "Unknown letter used in map creation? ";
				World::me->pause();
			}
		}
	}
}

World* World::me;

int World::forcePerDamage=200;
int World::curPath=0;
int World::curTick=0;

std::list<Living*> World::activeThings;
LivingQueue World::activeQueue;

Entity* World::getEntId(int targetId) {
	if(entities.count(targetId)==0)
	{
		std::cout << "Trying to get an id that isn't an entity? " << targetId;
		pause();
		return NULL;
	}

	if(entities[targetId]->id != targetId)
	{
		std::cout << "What the fuck at getEntId? " << targetId;
		pause();
		return NULL;
	}

	return entities[targetId];
}

void World::addRefresher(Living* thing, bool refreshNow) {
	// TODO: check if this thing already has a part of its refresh blob in the living queue already and only add if not?
	refreshQueue.push(thing);

	if(refreshNow)
	{
		handleRefresh();
	}
}

void World::handleRefresh() {
	while(!refreshQueue.empty())
	{
		refreshQueue.front()->fullRefresh();
		refreshQueue.pop();
	}
}


void World::addBlock(Block* block) {
	entities.insert(std::pair<int,Entity*>(block->id,block));

	//TODO: delete the old terrain

	if(block->isAlive)
	{
		activeThings.push_back(block);
		activeQueue.push(block);
	}

	if(cube[block->xPos][block->yPos][block->zPos]->block!=NULL)
	{
		remBlock(cube[block->xPos][block->yPos][block->zPos]->block);
	}

	cube[block->xPos][block->yPos][block->zPos]->block=block;
}

void World::moveBlock(Block* block, int x, int y, int z) {
	if(cube[x][y][z]->block->species!="Empty")
	{
		std::cout << "Trying to move a block from a to b, but theres already a non-empty block there? What do?";
		pause();
	}

	remBlock(cube[block->xPos][block->yPos][block->zPos]->block);

	cube[x][y][z]->block=block;

	block->xPos=x;
	block->yPos=y;
	block->zPos=z;
}

void World::remBlock(Block* block) {
	// add to terrain list? Why bother?

	//TODO: delete the old terrain

	if(block->initStatus!=1)
	{
		block->initStatus=1;

		cube[block->xPos][block->yPos][block->zPos]->block=new Empty(block->xPos, block->yPos, block->zPos);

		while(!stati.empty())
		{
			stati.front()->dead(block);
		}

		if(block->myGrav!=NULL)
		{
			block->myGrav->disown(block);
		}

		block->onDie();

		block->xPos=-666;
		block->yPos=-666;
		block->zPos=-666;
	}
}


void World::addUnit(Unit* guy) {
	entities.insert(std::pair<int,Entity*>(guy->id,guy));
	units.push_back(guy);

	if(guy->isAlive)
	{
		activeThings.push_back(guy);
		activeQueue.push(guy);
	}

	guy->initStatus=1;

	cube[guy->xPos][guy->yPos][guy->zPos]->addUnit(guy);

	guy->fullRefresh();
}

void World::moveUnit(Unit* guy, int x, int y, int z) {
	// TODO: add an int for normal move / only organ move / this + everyone attached move / teleport move / else?
	// SHOULD ONLY BE CALLED FROM TRYMOVE CURRENTLY


		// Unit::Trymove
	// If moveact needed, gets / uses one
	// Letmove check, which checks if canDragMove
	// Collide check for anything at our target
	// tryDragMove, which will move everyone we're dragging or drop them

		// World::moveUnit
	// FUCK checking if we can or not
	// If being held by someone, can't move

	// TODO: if something is embedded in another person and we're holding that thing, unembed it?

	// TODO: currently we drag people catterpillar style, them into our square then we move. Turtle style aka us move then they get to one of our close 3 squares better?

	if(guy->xPos==x && guy->yPos==y && guy->zPos==z)
	{
		return;
	}

	cube[guy->xPos][guy->yPos][guy->zPos]->remUnit(guy);

	cube[x][y][z]->addUnit(guy);

	int oldX=guy->xPos;
	int oldY=guy->yPos;
	int oldZ=guy->zPos;
	guy->xPos=x;
	guy->yPos=y;
	guy->zPos=z;

	std::vector<Item*> parts=guy->getBlob(true, 1, 3, 3, guy, 2, 0);
	for(unsigned int i=0;i<parts.size();i++)
	{
		submoveItem(parts[i], x, y, z);
	}

	guy->moved(x, y, z, oldX, oldY, oldZ);
}

void World::remUnit(Unit* guy) {
	if(guy->initStatus!=2)
	{
		std::cout << "<" << guy->name(2) << " ded> ";
		guy->initStatus=2;

		cube[guy->xPos][guy->yPos][guy->zPos]->remUnit(guy);

		while(!guy->stati.empty())
		{
			guy->stati.front()->dead(guy);
		}

		guy->drop(NULL, false);

		if(guy->myGrav!=NULL) // Disown removes the unit's gravity if we have any, so if we remove ourselves here it works out?
		{
			guy->myGrav->disown(guy);
		}

		std::set<Item*> organs(guy->parts);
		std::set<Item*>::iterator limb;

		while(!guy->parts.empty())
		{
			Item* obj=(*guy->parts.begin());
			guy->detach(obj, false);
			obj->disowned(false);
		}

		for(limb=organs.begin(); limb!=organs.end(); limb++)
		{
			(*limb)->fullRefresh();
		}

		guy->onDie();

		handleRefresh();

		guy->xPos=-666;
		guy->yPos=-666;
		guy->zPos=-666;
	}
}


Item* World::addItem(Item* newObj, Unit* guy, Item* thing, ItemCarryStatus initStatus) {
	// ARMORING if new object is covering target item, ARMORED if obj should be covering the new thing

	entities.insert(std::pair<int,Entity*>(newObj->id,newObj));
	items.push_back(newObj);

	if(newObj->isAlive)
	{
		activeThings.push_back(newObj);
		activeQueue.push(newObj);
	}

	if(initStatus==GROUND)
	{
		cube[newObj->xPos][newObj->yPos][newObj->zPos]->addItem(newObj);
		newObj->isHidden=false;
	}
	else if(initStatus==BRAIN)
	{
		if(thing==NULL)
		{
			guy->attach(newObj, true); // TODO: correct? claiming SHOULd be before attaching, but if we have no parts it causes errors
			guy->tryClaim(newObj, false);
		}
		else
		{
			thing->attach(newObj, true, false);
		}
	}
	else if(initStatus==ORGAN)
	{
		if(thing==NULL)
		{
			//TODO: possibly bad? sometimes we want to start with the body for init purposes, but make sure its not left with no coreparts
			guy->attach(newObj, false);
			guy->tryClaim(newObj, false);
		}
		else
		{
			thing->attach(newObj, false, false);
		}
	}
	else if(initStatus==ARMORING)
	{
		thing->armortach(newObj, false);
	}
	else if(initStatus==ARMORED)
	{
		newObj->armortach(thing, false);
	}
	else if(initStatus==HELD)
	{
		thing->grab(newObj, false);
	}
	else if(initStatus==STORED)
	{
		thing->store(newObj, false);
	}
	else if(initStatus==EMBEDDING)
	{
		thing->embed(newObj, false);
	}
	else if(initStatus==EMBEDDED)
	{
		newObj->embed(thing, false);
	}
	else if(initStatus==AUTO)
	{
		if(thing!=NULL)
		{
			thing->attach(newObj, false, false);
		}
		else
		{
			std::cout << "Item " << newObj->name(2) << " added with initStatus auto, but its not being connected to a thing?";
			pause();
		}
	}
	else
	{
		std::cout << "Unknown initStatus while adding item " << newObj->name(2);

		if(guy!=NULL)
		{
			std::cout << " to unit " << guy->name(2);
		}

		pause();
	}

	newObj->initStatus=1;

	addRefresher(newObj, true);

	return newObj;
}

void World::moveItem(Item* obj, int x, int y, int z) {
	if(x<0 || y<0 || z<0)
	{
		std::cout << "Item " << obj->name(2) << " is trying to move to a negative value? " << x << " " << y << " " << z;
		pause();
	}

	if(obj->xPos==x && obj->yPos==y && obj->zPos==z)
	{
		return;
	}

	if(obj->bestOwners().empty())
	{
		std::vector<Item*> myBlob=obj->getBlob(1, 3, 3, 3, NULL, 0, 0);

		std::cout << "[ " << obj->name(2) << " mov to " << x << " " << y << "] ";

		for(unsigned int i=0;i<myBlob.size();i++)
		{
			submoveItem(myBlob[i], x, y, z);
		}
	}
	else
	{
		// TODO: if someone is holding another unit's part and the held unit dies, we bring the held part into our square, meaning we can use this here
//		std::cout << "Item " << obj->name(2) << " is using moveItem when it has an owner " << obj->bestOwner()->name(2) << "? item is at  " << obj->xPos << " " << obj->yPos << " " << obj->zPos;
		//pause();

		submoveItem(obj, x, y, z);
	}
}

void World::submoveItem(Item* obj, int x, int y, int z) {
	if(x<0 || y<0 || z<0)
	{
		std::cout << "Item " << obj->name(2) << " is trying to move to a negative value? " << x << " " << y << " " << z;
		pause();
	}

//	std::cout << "[ " << obj->name(2) << " mov to " << x << " " << y << "] ";

	if(!obj->isHidden)
	{
		cube[obj->xPos][obj->yPos][obj->zPos]->remItem(obj);

		cube[x][y][z]->addItem(obj);
	}

	int oldX=obj->xPos;
	int oldY=obj->yPos;
	int oldZ=obj->zPos;
	obj->xPos=x;
	obj->yPos=y;
	obj->zPos=z;

	obj->moved(x, y, z, oldX, oldY, oldZ);
}

void World::hideItem(Item* obj, Entity* hider) {
	if(!obj->isHidden)
	{
		cube[obj->xPos][obj->yPos][obj->zPos]->remItem(obj);
		obj->isHidden=true;

		if(hider!=NULL && obj->xPos!=hider->xPos && obj->yPos!=hider->yPos && obj->zPos!=hider->zPos)
		{
			obj->xPos=hider->xPos;
			obj->yPos=hider->yPos;
			obj->zPos=hider->zPos;
		}
	}
//	else if(obj->carryStatus==JUST_ADDED)
//	{
//		obj->isHidden=true; // It starts out hidden and not on the ground, and it's carrystatus should immidiately be changed just after this in addItem somehow
//	}
//	else if(gameStatus!=0)
//	{
//		std::cout << obj->name(2) << " is trying to be made hidden when its hidden already???" <<std::endl;
//		pause();
//		return;
//	}
}

void World::unhideItem(Item* obj) {
	if(obj->isHidden && obj->initStatus!=2)
	{
		std::cout << "(" << obj->name(2) << " fell to the floor!) " << std::endl;
		cube[obj->xPos][obj->yPos][obj->zPos]->addItem(obj);
		obj->isHidden=false;
	}
}

void World::remItem(Item* obj) {
	if(obj->initStatus!=2)
	{
		obj->initStatus=2;

		std::cout << "<" << obj->name(2) << " ded> " << std::endl;

		while(!obj->stati.empty())
		{
			obj->stati.front()->dead(obj);
		}

		if(obj->holding!=NULL)
		{
			obj->drop(false);
		}

		while(!obj->holders.empty())
		{
			(*obj->holders.begin())->drop(false);
		}

		if(obj->storer!=NULL)
		{
			obj->storer->unstore(obj, false);
		}

		while(!obj->storing.empty())
		{
			obj->unstore(*obj->storing.begin(), false);
		}

//		if(obj->armor!=NULL)
//		{
//			obj->armorsever(); Needed? we sever armor when we sever anyways
//		}

		while(!obj->attached.empty())
		{
			obj->sever(NULL, false);
		}

		if(obj->owner!=NULL) // If you move this above severing everything, say why you did it plz and change unit::Dead
		{
			obj->owner->dead(obj);
		}

		if(obj->myGrav!=NULL)
		{
			obj->myGrav->disown(obj);
		}

		cube[obj->xPos][obj->yPos][obj->zPos]->remItem(obj);

		obj->onDie();

		obj->xPos=-666;
		obj->yPos=-666;
		obj->zPos=-666;

		handleRefresh();
	}
}


int World::tryMoveThing(int x, int y, int z, Entity* thing, bool actMove) {
	// actMove: only affects units, if true they'll try and use a movement action to make the move
	// Should return: -3 = out of bounds target, -2 = couldn't letMove, -1 = already at target square, 0 = moved, 1+ = id of blocking entity

	if(thing==NULL)
	{
		std::cout << "Why are we trying to world movething on a NULL?" << std::endl;
		pause();
	}
	else if(thing->order==UNIT)
	{
		Unit* guy=dynamic_cast<Unit*>(thing);
		return guy->tryMove(x, y, z, NULL, actMove, NULL, NULL);
	}
	else if(thing->order==ITEM)
	{
		Item* obj=dynamic_cast<Item*>(thing);
		return obj->tryMove(x, y, z, NULL);
	}
	else if(thing->order==BLOCK)
	{
		Block* blk=dynamic_cast<Block*>(thing);
		return blk->tryMove(x, y, z, NULL);
	}
	else
	{
		std::cout << "How the hell is moveThing being called on " << thing->name(2) << " that aint an item or unit?" << std::endl;
		pause();
	}

	return -666;
}

void World::moveThing(int x, int y, int z, Entity* thing) {
	// TODO: Pure movement, no checking if its possible. When do we need this?

	if(thing==NULL)
	{
		std::cout << "Why are we trying to world movething on a NULL?" << std::endl;
		pause();
	}
	else if(thing->order==UNIT)
	{
		Unit* guy=dynamic_cast<Unit*>(thing);
		moveUnit(guy, x, y, z);
	}
	else if(thing->order==ITEM)
	{
		Item* obj=dynamic_cast<Item*>(thing);
		moveItem(obj, x, y, z);
	}
	else if(thing->order==BLOCK)
	{
		Block* blk=dynamic_cast<Block*>(thing);
		moveBlock(blk, x, y, z);
	}
	else
	{
		std::cout << "How the hell is moveThing being called on " << thing->name(2) << " that aint an item or unit?" << std::endl;
		pause();
	}
}


void World::addStatus(Status* effect, Entity* thing, bool copying) {
	stati.push_back(effect);

	if(!thing->letInfect(effect))
	{
		effect->blocked();
		return;
	}

	effect->victim=thing;

	thing->stati.push_back(effect);
	if(thing->stati.size()>1)
	{
		Status* temp;
		int i=thing->stati.size()-2;
		while(i>=0 && thing->stati[i]->priority < thing->stati[i+1]->priority)
		{
			temp=thing->stati[i];
			thing->stati[i]=thing->stati[i+1];
			thing->stati[i+1]=temp;
			i--;
		}
	}

	if(effect->isAlive)
	{
		activeThings.push_back(effect);
		activeQueue.push(effect);
	}

	effect->initStatus=1;

	thing->fullRefresh();

	effect->onInfect();
}

void World::remStatus(Status* effect) {
	if(effect->initStatus!=2)
	{
		effect->initStatus=2;

		std::cout << "[" << effect->name(2) << " was removed!]";

		if(effect->victim!=NULL)
		{
			for(unsigned int i=0; i<effect->victim->stati.size(); i++)
			{
				if(effect->victim->stati[i]==effect)
				{
					effect->victim->stati.erase(effect->victim->stati.begin()+i);
					break;
				}
			}

			effect->victim->fullRefresh();
		}

		effect->onDie();
	}
	else
	{
		std::cout << "A status is being world removed twice? " << std::endl;
		World::me->pause();
	}
}


void World::addGravity(Gravity* momentum) {
	if(momentum->victim->myGrav!=NULL)
	{
		std::cout << "Just a double check, but we're fusing a gravity into another gravity here";
		momentum->fuseInto(momentum->victim->myGrav);
		momentum->initStatus=2;
		return;
	}

	if(momentum->victim->order==ITEM)
	{
		// TODO: what here?
		// TODO: held object knocked away due to impact?
		// TODO: object embedded into a unit?

		Item* obj=dynamic_cast<Item*>(momentum->victim);
		if(obj->owner!=NULL)
		{
			momentum->victim=obj->owner;
		}

//		if(obj->bestOwners().empty())
//		{
//			momentum->victim=obj->bestOwner();
//		}
	}

	momentum->claim(momentum->victim);

	activeThings.push_back(momentum);
	activeQueue.push(momentum);

	momentum->initStatus=1;

	momentum->victim->fullRefresh();
}

void World::remGravity(Gravity* momentum) {
	if(momentum->initStatus!=2)
	{
		momentum->initStatus=2;

		//std::cout << "[ Gravity " << momentum->id << " on the " << momentum->victim->species << " was removed!]" << std::endl;

		Entity* oldVictim=momentum->victim;

		while(momentum->victim!=NULL)
		{
			//	std::cout << momentum->victim->name(2) << std::endl;
			momentum->disown(momentum->victim);
		}

		if(oldVictim!=NULL)
		{
			oldVictim->fullRefresh();
		}
	}
//	else
//	{
//		std::cout << "A gravity is being world removed twice? " << std::endl;
//		World::me->pause();
//	}
}


std::queue<Square*> World::getNear(int x, int y, int z) {
	std::queue<Square*> around;
	for(int i=std::max(x-1, 0); i<=std::min(x+1, xMax-1); i++)
	{
		for(int j=std::max(y-1, 0); j<=std::min(y+1, yMax-1); j++)
		{
			for(int k=std::max(z-1, 0); k<=std::min(z+1, zMax-1); k++)
			{
				around.push(cube[i][j][k]);
			}
		}
	}

//
//	if(z>0) // below
//	{
//		around.push(cube[x][y][z-1]); // C
//		if(x>0 && y>0)
//			around.push(cube[x-1][y-1][z-1]); // NE
//		if(x>0)
//			around.push(cube[x-1][ y ][z-1]); // N
//		if(x>0 && y<yMax-1)
//			around.push(cube[x-1][y+1][z-1]); // NW
//		if(y<yMax-1)
//			around.push(cube[ x ][y+1][z-1]); // W
//		if(x<xMax-1 && y<yMax-1)
//			around.push(cube[x+1][y+1][z-1]); // SW
//		if(x<xMax-1)
//			around.push(cube[x+1][ y ][z-1]); // S
//		if(x<xMax-1 && y>0)
//			around.push(cube[x+1][y-1][z-1]); // SE
//		if(y>0)
//			around.push(cube[ x ][y-1][z-1]); // E
//	}
//
//	if(x>0 && y>0)
//		around.push(cube[x-1][y-1][ z ]); // NE
//	if(x>0)
//		around.push(cube[x-1][ y ][ z ]); // N
//	if(x>0 && y<yMax-1)
//		around.push(cube[x-1][y+1][ z ]); // NW
//	if(y<yMax-1)
//		around.push(cube[ x ][y+1][ z ]); // W
//	if(x<xMax-1 && y<yMax-1)
//		around.push(cube[x+1][y+1][ z ]); // SW
//	if(x<xMax-1)
//		around.push(cube[x+1][ y ][ z ]); // S
//	if(x<xMax-1 && y>0)
//		around.push(cube[x+1][y-1][ z ]); // SE
//	if(y>0)
//		around.push(cube[ x ][y-1][ z ]); // E
//
//	if(z<zMax-1)
//	{
//		around.push(cube[x][y][z+1]); // C
//		if(x>0 && y>0)
//			around.push(cube[x-1][y-1][z+1]); // NE
//		if(x>0)
//			around.push(cube[x-1][ y ][z+1]); // N
//		if(x>0 && y<yMax-1)
//			around.push(cube[x-1][y+1][z+1]); // NW
//		if(y<yMax-1)
//			around.push(cube[ x ][y+1][z+1]); // W
//		if(x<xMax-1 && y<yMax-1)
//			around.push(cube[x+1][y+1][z+1]); // SW
//		if(x<xMax-1)
//			around.push(cube[x+1][ y ][z+1]); // S
//		if(x<xMax-1 && y>0)
//			around.push(cube[x+1][y-1][z+1]); // SE
//		if(y>0)
//			around.push(cube[ x ][y-1][z+1]); // E
//
//	}

	return around;
}

std::vector<Unit*> World::getNearbyUnits(int x, int y, int z, double radius, bool onlyTargetable) {
	std::vector<Unit*> nearby;

	for(int i=std::max(1,x-int(radius)); i<=std::min(xMax-2,x+int(radius)); i++)
	{
		for(int j=std::max(1,y-int(radius)); j<=std::min(yMax-2,y+int(radius)); j++)
		{
			for(int k=std::max(1,z-int(radius)); k<=std::min(zMax-2,z+int(radius)); k++)
			{
				if(distance(x,y,z,i,j,k)<=radius && (!onlyTargetable || tryTargetTo(x,y,z,i,j,k,true,1)==NULL)) // TODO: true in all cases? also adjust for when sight comes in
				{
					std::list<Unit*>::iterator guy;
					for(guy=cube[i][j][k]->units.begin(); guy!=cube[i][j][k]->units.end(); guy++)
					{
						nearby.push_back(*guy);
					}
				}
			}
		}
	}
	return nearby;
}

std::vector<Item*> World::getNearbyItems(int x, int y, int z, double radius, bool onlyTargetable, int includeUnitParts, Unit* ignoreMe) {
	// includeUnitParts: 0 = ignore units and their parts, 1 = include ONLY TARGETABLE PARTS, 2 = include all their parts

	std::vector<Item*> nearby;
	std::set<Item*> checked;

	for(int i=std::max(1,x-int(radius)); i<=std::min(xMax-2,x+int(radius)); i++)
	{
		for(int j=std::max(1,y-int(radius)); j<=std::min(yMax-2,y+int(radius)); j++)
		{
			for(int k=std::max(1,z-int(radius)); k<=std::min(zMax-2,z+int(radius)); k++)
			{
				if(distance(x,y,z,i,j,k)<=radius && (!onlyTargetable || tryTargetTo(x,y,z,i,j,k,true,1)==NULL))
				{
					std::list<Item*>::iterator obj;
					for(obj=cube[i][j][k]->items.begin(); obj!=cube[i][j][k]->items.end(); obj++)
					{
						nearby.push_back(*obj);
					}

					if(includeUnitParts!=0)
					{
						std::list<Unit*>::iterator guy;
						for(guy=cube[i][j][k]->units.begin(); guy!=cube[i][j][k]->units.end(); guy++)
						{
							if((*guy)!=ignoreMe)
							{
								std::vector<Item*> results=(*guy)->getBlob(true, 3, 3, 3, (*guy), 2, 0); // TODO: if unitparts==1, attackable parts only
								for(unsigned int l=0;l<results.size();l++)
								{
									if(checked.count(results[l])==0) // TODO: also check if they're in the same square? they should be, considering the 2, 0, 0 above
									{
										checked.insert(results[l]);
										nearby.push_back(results[l]);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return nearby;
}

std::vector<Square*> World::getNearbySquares(int x, int y, int z, double radius, bool onlyTargetable) {
	std::vector<Square*> nearby;

	for(int i=std::max(1,x-int(radius)); i<=std::min(xMax-2,x+int(radius)); i++)
	{
		for(int j=std::max(1,y-int(radius)); j<=std::min(yMax-2,y+int(radius)); j++)
		{
			for(int k=std::max(1,z-int(radius)); k<=std::min(zMax-2,z+int(radius)); k++)
			{
				if(distance(x,y,z,i,j,k)<=radius && (!onlyTargetable || tryTargetTo(x,y,z,i,j,k,true,1)==NULL)) // TODO: true in all cases? also adjust for when sight comes in
				{
					nearby.push_back(cube[i][j][k]);
				}
			}
		}
	}

	return nearby;
}


double World::distance(int hereX, int hereY, int hereZ, int thereX, int thereY, int thereZ) {
	double xDistance=hereX-thereX;
	double yDistance=hereY-thereY;
	double zDistance=hereZ-thereZ;
	return sqrt((xDistance*xDistance)+(yDistance*yDistance)+(zDistance*zDistance));
}

double World::heuristic(int hereX, int hereY, int hereZ, int thereX, int thereY, int thereZ) {
	int maxDist=abs(hereX-thereX);
	maxDist=std::max(maxDist, abs(hereY-thereY));
	maxDist=std::max(maxDist, abs(hereZ-thereZ));
	return maxDist;
}

int World::gcd(int a, int b) {
	while(true)
	{
		if(a==0)
		{
			return b;
		}
		b%=a;
		if(b==0)
		{
			return a;
		}
		a%=b;
	}
	std::cout << "How the fuck did we get past a true while loop at GCF?";
	pause();
	return -1;
}

int World::lcm(int a, int b) {
	// TODO: if 0 is input, returns the other number? so LCM of 0 / 40 should be 40, correct?

	if(b==0)
	{
		return a;
	}
	else if(a==0) // this part is caught in GCD
	{
		return b;
	}

	int GCD=gcd(a, b);

	if(GCD==0)
	{
		return 0;
	}
	else
	{
		return a*b/GCD;
	}
}

int World::random(int min, int max) {
	if(min==max)
	{
		return min;
	}

	//TODO: Max is exclusive, ie max of 4 = 0-3, 1=0-0
	int result=((max-min)*rand())/float(RAND_MAX);
	while(result<0 || result>=(max-min))
	{
		result=((max-min)*rand())/float(RAND_MAX);
	}
	return result+min;
}


bool World::canSeeTo(int x, int y, int z, int xx, int yy, int zz, bool inner, int howClose) {
	return tryTargetTo(x, y, z, xx, yy, zz, inner, howClose)==NULL;
}

Entity* World::tryTargetTo(int x, int y, int z, int xx, int yy, int zz, bool inner, int howClose) {
	// Returns whatever entity we hit reaching towards our target goal, or NULL if we can raycast there with no blockers

	// howClose
	// TODO: 0 = including INSIDE target square AND ALSO WITH NO OTHER UNITS INSIDE? IE: charging into a square where hitting anyone would interupt you and collide with them?
	// 1 = including INSIDE target square, IE throwing something at a guy inside target square
	// TODO: up to but must be walkable. When would we use this, as opposed to below?
	// 2 = only up to but must be targetable INTO that square, IE teleporting to the closest square to a guy to punch him in the face a second later
	// 3 = up to but must be targetable UP TO that square, IE teleporting to the closest square to a wall to mine it a second later
	// TODO: 4 = any adjacent square, when would this be used ever?
	// Above also only matters if we're not interrupted by blockers beforehand

	Entity* closeHit=NULL;

	int mult=(inner ? 1 : 2); // If we're checking inner square to inner square, we want 1-2-3 for inner+middle quadrents, otherwise 0-2-4 for edge+middle quadrents

	for(int i=0;i<=2;i++)
	{
		for(int j=0;j<=2;j++)
		{
			for(int k=0;k<=2;k++)
			{
				for(int ii=0;ii<=2;ii++)
				{
					for(int jj=0;jj<=2;jj++)
					{
						for(int kk=0;kk<=2;kk++)
						{
							Entity* newHit=intRaycastHit(x, 2-mult+(i*mult), y, 2-mult+(j*mult), z, 2-mult+(k*mult), xx, 2-mult+(ii*mult), yy, 2-mult+(jj*mult), zz, 2-mult+(kk*mult), howClose);

							if(newHit==NULL)
							{
								return NULL;
							}

							if(closeHit==NULL || distance(x, y, z, newHit->xPos, newHit->yPos, newHit->zPos) < distance(x, y, z, closeHit->xPos, closeHit->yPos, closeHit->zPos))
							{
								closeHit=newHit;
							}
						}
					}
				}
			}
		}
	}

	return closeHit;
}

Entity* World::intRaycastHit(int x, int xAdd, int y, int yAdd, int z, int zAdd, int xx, int xxAdd, int yy, int yyAdd, int zz, int zzAdd, int howClose) {
	// Returns whatever entity we hit reaching towards our target goal, or NULL if we can raycast there with no blockers
	// Whatever you change here, also change in intRaycastPath

	if(x==1 && y==1 && z==1 &&  			xx==2 && yy==10 && zz==2 &&		 xAdd==2 && yAdd==0 && zAdd==0 &&		 xxAdd==4 && yyAdd==0 && zzAdd==0)
	{
//		std::cout << "here comes the fuckery " << std::endl;
	}

	int curX=x; // Cur x/y/z square we think we're at
	int curY=y;
	int curZ=z;

	int xLeft=abs(x-xx); // countdown of how many squares are left in each direction to reach our objectives
	int yLeft=abs(y-yy);
	int zLeft=abs(z-zz);

	if(xLeft==0 && yLeft==0 && zLeft==0)
	{
//		std::cout << "trying to canTargetTo our own square at " << x << " " << y << " " << z;
//		pause();
		return NULL;
	}

	int xDir=(x<=xx ? 1 : -1); // If we're moving positive or negative direction. If we're NOT (x==xx), will be handled later
	int yDir=(y<=yy ? 1 : -1);
	int zDir=(z<=zz ? 1 : -1);

	int xDist=abs((x*4+xAdd)-(xx*4+xxAdd)); // The distance between our start point and our destination, aka starting at x(xAdd) = 1(0) and going to 4(2) = a total of 4(+0) - 16(+2) = 14
	int yDist=abs((y*4+yAdd)-(yy*4+yyAdd));
	int zDist=abs((z*4+zAdd)-(zz*4+zzAdd));

	if(xDist==0 && xLeft!=0) // In the edge case that we're moving 1 square but start / end on the same edge,
	{
		xDist=-4; // We want to cross over int that direction exactly at the halfway point, which we can do by faking that we're actually at x.5 going to xx.5 with no ill effects
	}

	if(yDist==0 && yLeft!=0)
	{
		yDist=-4;
	}

	if(zDist==0 && zLeft!=0)
	{
		zDist=-4;
	}

	int LCM=lcm(lcm(abs(xDist), abs(yDist)), abs(zDist)); // We use LCM to reduce the max values to something smaller / simpler, aka from 3-6-12 to 1-2-4

	int xCooldown=(xDist==0 ? 10000 : LCM/abs(xDist)); // This makes shorter distances (2 tiles x vs 40 tiles y) actually become higher maxes, as we cross their tiles less frequently opposed to far distances
	int yCooldown=(yDist==0 ? 10000 : LCM/abs(yDist)); // If we're not moving in that direction however, maxXYZ is 0 from before, and now should be the maximum int because we'll never move that way
	int zCooldown=(zDist==0 ? 10000 : LCM/abs(zDist));

	while(xCooldown%4!=0 || yCooldown%4!=0 || zCooldown%4!=0) // However, we always want to be able to start at 'half/quarterway' between the tiles in the nextXYZ section below,
	{
		xCooldown*=2;//  so the end results must be divisible by 4
		yCooldown*=2;
		zCooldown*=2;
	}

	int nextX=(xDir==1 ? (4-xAdd)*(xCooldown/4) : xAdd*(xCooldown/4)); // How far away we are from crossing the next x/y/z edge into the next square, starting depending on our xyzAdds
	int nextY=(yDir==1 ? (4-yAdd)*(yCooldown/4) : yAdd*(yCooldown/4));
	int nextZ=(zDir==1 ? (4-zAdd)*(zCooldown/4) : zAdd*(zCooldown/4));


	if(xLeft==0) // If we're not moving in an xyz direction,
	{
		xDir=0; // Set our xyzDir to 0 instead of 1 and make it so we'll never reach the edge by the time we reach our destination
		nextX=xCooldown; // xCooldown should be the maximum 100000 * whatever, so this will make it never reach the edge          TODO: correct?
	}
	else if(xDist<0) // If we're actually a straight line but lied and want to cross over at exactly halfway,
	{
		nextX=xCooldown/2; // We make it so we're set to cross over at the halfway mark, as the distance is always 1 tile and here we're set to start at x+0.5 to xx+0.5
	}

	if(yLeft==0)
	{
		yDir=0;
		nextY=yCooldown;
	}
	else if(yDist<0)
	{
		nextY=yCooldown/2;
	}

	if(zLeft==0)
	{
		zDir=0;
		nextZ=zCooldown;
	}
	else if(zDist<0)
	{
		nextZ=zCooldown/2;
	}


	bool xMove=false; // If we're moving in an xyz direction each step, checked by comparing which edge we're closest to
	bool yMove=false;
	bool zMove=false;

	while(curX!=xx || curY!=yy || curZ!=zz)
	{
		int min=std::min(std::min(nextX, nextY), nextZ); // we find out which edge we hit next, and set that as the number of steps we walk towards each edge

		if(nextX==min) // If min = the number of steps to reach an edge, set xyzMove to the direction we're going
		{
			nextX=xCooldown;
			xMove=true;

			if(xLeft==0)// && distance(curX, curY, curZ, xx, yy, zz)<2) // Edge case of "this wants to go diagonal but we're adjacent to the goal and only need to go one way"
			{
				xMove=false;
			}
		}
		else // Otherwise, increment our distance to the edge by however much we moved towards the nearest edge
		{
			nextX-=min;
			xMove=false;
		}

		if(nextY==min)
		{
			nextY=yCooldown;
			yMove=true;

			if(yLeft==0)// && distance(curX, curY, curZ, xx, yy, zz)<2)
			{
				yMove=false;
			}
		}
		else
		{
			nextY-=min;
			yMove=false;
		}

		if(nextZ==min)
		{
			nextZ=zCooldown;
			zMove=true;

			if(zLeft==0) // && distance(curX, curY, curZ, xx, yy, zz)<2)
			{
				zMove=false;
			}
		}
		else
		{
			nextZ-=min;
			zMove=false;
		}

		int minFail=((xMove && yMove) || (xMove && zMove) || (yMove && zMove)) ? 4 : 2; // Moving more than one direction = moving through an exact corner = less strict wall requirements

		for(int i=0; i<=(xMove ? 1 : 0);i++)
		{
			for(int j=0; j<=(yMove ? 1 : 0);j++)
			{
				for(int k=0; k<=(zMove ? 1 : 0);k++)
				{
					if(howClose<3 || curX+(i*xDir)!=xx || curY+(j*yDir)!=yy || curZ+(k*zDir)!=zz) // If we're aiming to get inside the square or not looking at our target yet, check the edges
					{
						Square* realCube=cube[curX+(i*xDir)][curY+(j*yDir)][curZ+(k*zDir)];

						if(xMove)
						{
							if(((i==0 && xDir==1) || (i==1 && xDir==-1)) && realCube->block->X>=minFail)
							{
								return realCube->block;
							}
							else if(((i==1 && xDir==1) || (i==0 && xDir==-1)) && realCube->block->NotX>=minFail)
							{
								return realCube->block;
							}
						}

						if(yMove)
						{
							if(((j==0 && yDir==1) || (j==1 && yDir==-1)) && realCube->block->Y>=minFail)
							{
								return realCube->block;
							}
							else if(((j==1 && yDir==1) || (j==0 && yDir==-1)) && realCube->block->NotY>=minFail)
							{
								return realCube->block;
							}
						}

						if(zMove)
						{
							if(((k==0 && zDir==1) || (k==1 && zDir==-1)) && realCube->block->Z>=minFail)
							{
								return realCube->block;
							}
							else if(((k==0 && zDir==1) || (k==1 && zDir==-1)) && realCube->block->NotZ>=minFail)
							{
								return realCube->block;
							}
						}
					}
				}
			}
		}

		curX+=(xMove ? xDir : 0);
		curY+=(yMove ? yDir : 0);
		curZ+=(zMove ? zDir : 0);

		xLeft-=(xMove ? 1 : 0);
		yLeft-=(yMove ? 1 : 0);
		zLeft-=(zMove ? 1 : 0);

		if(xLeft<0 || yLeft<0 || zLeft<0)
		{
			std::cout << "overflow past our goal in canTargetTo: lefts are " << xLeft << " " << yLeft << " " << zLeft << " from "
					<< x << " " << y << " " << z << " at " << curX << " " << curY << " " << curZ << " to " << xx << " " << yy << " " << zz
					<< " with adds " << xAdd << " " << yAdd << " " << zAdd << " and " << xxAdd << " " << yyAdd << " " << zzAdd;
			pause();
			return NULL;
		}

		if(howClose<3 || curX!=xx || curY!=yy || curZ!=zz) // If we're looking to go inside the target square or if we're not at the target yet
		{
			if(cube[curX][curY][curZ]->block->center==3) // If the center's solid we can't go through it, even if the projectile would only be on the very very very edge
			{
				return cube[curX][curY][curZ]->block;
			}

//			std::list<Unit*>::iterator guy;
//			for(guy=cube[curX][curY][curZ]->units.begin(); guy!=cube[curX][curY][curZ]->units.end(); guy++)
//			{
//				if((*guy)->) 							TODO: wat here for checking if a unit blocks the path?
//				{
//					retur that dude
//				}
//			}
		}
	}

	return NULL;
}

std::queue<Square*> World::tryRaypathTo(int x, int y, int z, int xx, int yy, int zz, bool inner, int howClose) {
	// howClose
	// 1 = including INSIDE target square, IE throwing something at a guy inside target square
	// TODO: up to but must be walkable. When would we use this, as opposed to below?
	// 2 = only up to but must be targetable INTO that square, IE throwing something at the center of a target block hitting the middle
	// 3 = up to but must be targetable UP TO that square, IE throwing something at a targeted walled block hitting the edge
	// TODO: 4 = any adjacent square, when would this be used ever?
	// Above also only matters if we're not interrupted by blockers beforehand

	std::queue<Square*> failQue;
	Entity* closeHit=NULL;

	int bestI=-1;
	int bestJ=-1;
	int bestK=-1;
	int bestII=-1;
	int bestJJ=-1;
	int bestKK=-1;

	int mult=(inner ? 1 : 2); // If we're checking inner square to inner square, we want 1-2-3 for inner+middle quadrents, otherwise 0-2-4 for edge+middle quadrents

	for(int i=0;i<=2;i++)
	{
		for(int j=0;j<=2;j++)
		{
			for(int k=0;k<=2;k++)
			{
				for(int ii=0;ii<=2;ii++)
				{
					for(int jj=0;jj<=2;jj++)
					{
						for(int kk=0;kk<=2;kk++)
						{
							Entity* newHit=intRaycastHit(x, 2-mult+(i*mult), y, 2-mult+(j*mult), z, 2-mult+(k*mult), xx, 2-mult+(ii*mult), yy, 2-mult+(jj*mult), zz, 2-mult+(kk*mult), howClose);

							if(newHit==NULL)
							{
								return intRaycastPath(x, 2-mult+(i*mult), y, 2-mult+(j*mult), z, 2-mult+(k*mult), xx, 2-mult+(ii*mult), yy, 2-mult+(jj*mult), zz, 2-mult+(kk*mult), howClose);
							}

							if(closeHit==NULL || distance(x, y, z, newHit->xPos, newHit->yPos, newHit->zPos) < distance(x, y, z, closeHit->xPos, closeHit->yPos, closeHit->zPos))
							{
								closeHit=newHit;
								bestI=i;
								bestJ=j;
								bestK=k;
								bestII=ii;
								bestJJ=jj;
								bestKK=kk;
							}
						}
					}
				}
			}
		}
	}

	return intRaycastPath(x, 2-mult+(bestI*mult), y, 2-mult+(bestJ*mult), z, 2-mult+(bestK*mult), xx, 2-mult+(bestII*mult), yy, 2-mult+(bestJJ*mult), zz, 2-mult+(bestKK*mult), howClose);
}


std::queue<Square*> World::intRaycastPath(int x, int xAdd, int y, int yAdd, int z, int zAdd, int xx, int xxAdd, int yy, int yyAdd, int zz, int zzAdd, int howClose) {
	// Returns the path up to our goal or up to the first square that gets blocked, sometimes resulting in an empty queue
	// Whatever you change here, also change in intRaycastHit

	std::queue<Square*> curQue;

	int curX=x; // Cur x/y/z square we think we're at
	int curY=y;
	int curZ=z;

	int xLeft=abs(x-xx); // countdown of how many squares are left in each direction to reach our objectives
	int yLeft=abs(y-yy);
	int zLeft=abs(z-zz);

	if(xLeft==0 && yLeft==0 && zLeft==0)
	{
//		std::cout << "trying to canTargetTo our own square at " << x << " " << y << " " << z;
//		pause();
		return curQue;
	}

	int xDir=(x<=xx ? 1 : -1); // If we're moving positive or negative direction. If we're NOT (x==xx), will be handled later
	int yDir=(y<=yy ? 1 : -1);
	int zDir=(z<=zz ? 1 : -1);

	int xDist=abs((x*4+xAdd)-(xx*4+xxAdd)); // The distance between our start point and our destination, aka starting at x(xAdd) = 1(0) and going to 4(2) = a total of 4(+0) - 16(+2) = 14
	int yDist=abs((y*4+yAdd)-(yy*4+yyAdd));
	int zDist=abs((z*4+zAdd)-(zz*4+zzAdd));

	if(xDist==0 && xLeft!=0) // In the edge case that we're moving 1 square but start / end on the same edge,
	{
		xDist=-4; // We want to cross over int that direction exactly at the halfway point, which we can do by faking that we're actually at x.5 going to xx.5 with no ill effects
	}

	if(yDist==0 && yLeft!=0)
	{
		yDist=-4;
	}

	if(zDist==0 && zLeft!=0)
	{
		zDist=-4;
	}

	int LCM=lcm(lcm(abs(xDist), abs(yDist)), abs(zDist)); // We use LCM to reduce the max values to something smaller / simpler, aka from 3-6-12 to 1-2-4

	int xCooldown=(xDist==0 ? 10000 : LCM/abs(xDist)); // This makes shorter distances (2 tiles x vs 40 tiles y) actually become higher maxes, as we cross their tiles less frequently opposed to far distances
	int yCooldown=(yDist==0 ? 10000 : LCM/abs(yDist)); // If we're not moving in that direction however, maxXYZ is 0 from before, and now should be the maximum int because we'll never move that way
	int zCooldown=(zDist==0 ? 10000 : LCM/abs(zDist));

	while(xCooldown%4!=0 || yCooldown%4!=0 || zCooldown%4!=0) // However, we always want to be able to start at 'half/quarterway' between the tiles in the nextXYZ section below,
	{
		xCooldown*=2;//  so the end results must be divisible by 4
		yCooldown*=2;
		zCooldown*=2;
	}

	int nextX=(xDir==1 ? (4-xAdd)*(xCooldown/4) : xAdd*(xCooldown/4)); // How far away we are from crossing the next x/y/z edge into the next square, starting depending on our xyzAdds
	int nextY=(yDir==1 ? (4-yAdd)*(yCooldown/4) : yAdd*(yCooldown/4));
	int nextZ=(zDir==1 ? (4-zAdd)*(zCooldown/4) : zAdd*(zCooldown/4));


	if(xLeft==0) // If we're not moving in an xyz direction,
	{
		xDir=0; // Set our xyzDir to 0 instead of 1 and make it so we'll never reach the edge by the time we reach our destination
		nextX=xCooldown; // xCooldown should be the maximum 100000 * whatever, so this will make it never reach the edge          TODO: correct?
	}
	else if(xDist<0) // If we're actually a straight line but lied and want to cross over at exactly halfway,
	{
		nextX=xCooldown/2; // We make it so we're set to cross over at the halfway mark, as the distance is always 1 tile and here we're set to start at x+0.5 to xx+0.5
	}

	if(yLeft==0)
	{
		yDir=0;
		nextY=yCooldown;
	}
	else if(yDist<0)
	{
		nextY=yCooldown/2;
	}

	if(zLeft==0)
	{
		zDir=0;
		nextZ=zCooldown;
	}
	else if(zDist<0)
	{
		nextZ=zCooldown/2;
	}

	bool xMove=false; // If we're moving in an xyz direction each step, checked by comparing which edge we're closest to
	bool yMove=false;
	bool zMove=false;

	while(curX!=xx || curY!=yy || curZ!=zz)
	{
		int min=std::min(std::min(nextX, nextY), nextZ); // we find out which edge we hit next, and set that as the number of steps we walk towards each edge

		if(nextX==min) // If min = the number of steps to reach an edge, set xyzMove to the direction we're going
		{
			nextX=xCooldown;
			xMove=true;

			if(xLeft==0)// && distance(curX, curY, curZ, xx, yy, zz)<2) // Edge case of "this wants to go diagonal but we're adjacent to the goal and only need to go one way"
			{
				xMove=false;
			}
		}
		else // Otherwise, increment our distance to the edge by however much we moved towards the nearest edge
		{
			nextX-=min;
			xMove=false;
		}

		if(nextY==min)
		{
			nextY=yCooldown;
			yMove=true;

			if(yLeft==0)// && distance(curX, curY, curZ, xx, yy, zz)<2)
			{
				yMove=false;
			}
		}
		else
		{
			nextY-=min;
			yMove=false;
		}

		if(nextZ==min)
		{
			nextZ=zCooldown;
			zMove=true;

			if(zLeft==0) // && distance(curX, curY, curZ, xx, yy, zz)<2)
			{
				zMove=false;
			}
		}
		else
		{
			nextZ-=min;
			zMove=false;
		}

		int minFail=((xMove && yMove) || (xMove && zMove) || (yMove && zMove)) ? 4 : 2; // Moving more than one direction = moving through an exact corner = less strict wall requirements

		for(int i=0; i<=(xMove ? 1 : 0);i++)
		{
			for(int j=0; j<=(yMove ? 1 : 0);j++)
			{
				for(int k=0; k<=(zMove ? 1 : 0);k++)
				{
					// If we're doing upTo, we dont check the exact square we're about to enter, but check if we can reach UPTO it including the walls touching it
					if(howClose<3 || curX+(i*xDir)!=xx || curY+(j*yDir)!=yy || curZ+(k*zDir)!=zz)
					{
						Square* realCube=cube[curX+(i*xDir)][curY+(j*yDir)][curZ+(k*zDir)];

						if(xMove)
						{
							if(((i==0 && xDir==1) || (i==1 && xDir==-1)) && realCube->block->X>=minFail)
							{
								return curQue;
							}
							else if(((i==1 && xDir==1) || (i==0 && xDir==-1)) && realCube->block->NotX>=minFail)
							{
								return curQue;
							}
						}

						if(yMove)
						{
							if(((j==0 && yDir==1) || (j==1 && yDir==-1)) && realCube->block->Y>=minFail)
							{
								return curQue;
							}
							else if(((j==1 && yDir==1) || (j==0 && yDir==-1)) && realCube->block->NotY>=minFail)
							{
								return curQue;
							}
						}

						if(zMove)
						{
							if(((k==0 && zDir==1) || (k==1 && zDir==-1)) && realCube->block->Z>=minFail)
							{
								return curQue;
							}
							else if(((k==0 && zDir==1) || (k==1 && zDir==-1)) && realCube->block->NotZ>=minFail)
							{
								return curQue;
							}
						}
					}
				}
			}
		}


		curX+=(xMove ? xDir : 0);
		curY+=(yMove ? yDir : 0);
		curZ+=(zMove ? zDir : 0);

		xLeft-=(xMove ? 1 : 0);
		yLeft-=(yMove ? 1 : 0);
		zLeft-=(zMove ? 1 : 0);

		if(xLeft<0 || yLeft<0 || zLeft<0)
		{
			std::cout << "overflow past our goal in intRayPath: lefts are " << xLeft << " " << yLeft << " " << zLeft << " from "
					<< x << " " << y << " " << z << " at " << curX << " " << curY << " " << curZ << " to " << xx << " " << yy << " " << zz
					<< " with adds " << xAdd << " " << yAdd << " " << zAdd << " and " << xxAdd << " " << yyAdd << " " << zzAdd;
			pause();
			return curQue;
		}

		// howClose
		// 1 = including INSIDE target square, IE throwing something at a guy inside target square
		// TODO: up to but must be walkable. When would we use this, as opposed to below?
		// 2 = only up to but must be targetable INTO that square, IE throwing something at the center of a target block hitting the middle block part
		// 3 = up to but must be targetable UP TO that square, IE throwing something at a targeted walled block hitting the edge
		// TODO: 4 = any adjacent square, when would this be used ever?
		// Above also only matters if we're not interrupted by blockers beforehand

		if(howClose<=2 || curX!=xx || curY!=yy || curZ!=zz)
		{
			if(cube[curX][curY][curZ]->block->center==3) // If the center's solid we can't go through it, even if the projectile would only be on the very very very edge
			{
				return curQue;
			}

			std::list<Unit*>::iterator guy;
			for(guy=cube[curX][curY][curZ]->units.begin(); guy!=cube[curX][curY][curZ]->units.end(); guy++)
			{
//				if((*guy)->) TODO: wat here for checking if a unit blocks the path?
//				{
//					retur curquerueue
//				}
			}
		}

		if(howClose>1 && curX==xx && curY==yy && curZ==zz)
		{
			return curQue;
		}

		curQue.push(cube[curX][curY][curZ]);
	}

	// TODO: could easily move this to the above while loop due to how howClose works, making it a true forever till it hits
	return curQue;
}


Square* World::starPath(Unit* seeker, int targetX, int targetY, int targetZ, std::vector<Actool*> movements, bool risky, int howClose) {
	//TODO: we dont want people pathOn-ing to squares they cant move into, so we cant return paths that include destinations that are walls ect
	// currently we have them only walk up one prior to the square they're trying to reach, including if its one away but we cant walk on it. Correct?

	// Returns: NULL = same square, -666 square = failed to path, normal square = next square to move onto

	// howClose
	// 1 = including INSIDE target square, IE going to explore to target point
	// TODO: up to but must be walkable. When would we use this, as opposed to below?
	// 2 = only up to but must be targetable INTO that square, IE charging an enemy hovering 1 tile above ground, but must path around a circular wall covering the edges around the x/y axis
	// 3 = up to but must be targetable UP TO that square, IE going to mine a solid wall
	// TODO: 4 = any adjacent square, when would this be used ever?

	if(seeker->xPos==targetX && seeker->yPos==targetY && seeker->zPos==targetZ)
	{
		return NULL;
	}


//	std::cout << "starpath to " << targetX << " " << targetY  << " " << targetZ << std::endl;

	curPath++;

	SquareQueue* toCheck=new SquareQueue();

	cube[seeker->xPos][seeker->yPos][seeker->zPos]->lastPath=curPath;
	cube[seeker->xPos][seeker->yPos][seeker->zPos]->steps=0;
	cube[seeker->xPos][seeker->yPos][seeker->zPos]->estDist=heuristic(seeker->xPos, seeker->yPos, seeker->zPos, targetX, targetY, targetZ);
	cube[seeker->xPos][seeker->yPos][seeker->zPos]->lastStep=NULL;

	toCheck->push(cube[seeker->xPos][seeker->yPos][seeker->zPos]);

	std::set<Square*> checked;
	double newSteps=0;

	while(toCheck->size()!=0)
	{
		Square* checking=toCheck->front();

		toCheck->pop();
		checked.insert(checking);

		for(std::queue<Square*> aroundMe=getNear(checking->xPos, checking->yPos, checking->zPos); !aroundMe.empty(); aroundMe.pop())
		{
			if(checked.count(aroundMe.front())!=0)
			{
				continue;
			}

//			std::cout << "	checking " << aroundMe.front()->xPos << " " << aroundMe.front()->yPos << " " << aroundMe.front()->zPos << " from " << checking->xPos << " " << checking->yPos << " " << checking->zPos << std::endl;

			bool canMove=false;

			for(unsigned int i=0;i<movements.size();i++)
			{
				if(movements[i]->couldAttempt(checking, aroundMe.front(), risky))
				{
					canMove=true;
					break;
				}
			}

//			bool canMove=(moveAct->actionSubtype==WALK && !risky && seeker->canWalk(checking, aroundMe.front())==NULL) ||
//							(moveAct->actionSubtype==WALK && risky && seeker->canRiskwalk(checking, aroundMe.front())==NULL) ||
//							(moveAct->actionSubtype==FLY && seeker->canFly(checking, aroundMe.front())==NULL) ||
//							(moveAct->actionSubtype==TELEPORT); //TODO: and CanTeleport?


			if(canMove && aroundMe.front()->xPos==2 && aroundMe.front()->yPos==1)
			{

//				std::cout << "	I'm dumb!" << std::endl;
				pause();
			}

			if(aroundMe.front()->xPos==targetX && aroundMe.front()->yPos==targetY && aroundMe.front()->zPos==targetZ)
			{
//				std::cout << "	Its the square i want!" << std::endl;





				if(canMove) // todo: remove and replace with below
				{
//					std::cout << "	AND I CAN MOVE THERE!" << std::endl;
					if(howClose==1)
					{
						aroundMe.front()->lastStep=checking;
						return aroundMe.front()->initStep();
					}
					else
					{
						return checking->initStep();
					}
				}





				if(howClose==1 && canMove)
				{
					aroundMe.front()->lastStep=checking;
					return aroundMe.front()->initStep();
				}

				if((howClose==2 && tryTargetTo(checking->xPos, checking->yPos, checking->zPos, aroundMe.front()->xPos, aroundMe.front()->yPos, aroundMe.front()->zPos, true, howClose)==NULL) ||
					(howClose==3 && tryTargetTo(checking->xPos, checking->yPos, checking->zPos, aroundMe.front()->xPos, aroundMe.front()->yPos, aroundMe.front()->zPos, true, howClose)==NULL))
				{
					return checking->initStep();
				}

//				std::cout << "	cant move there,,," << std::endl;
			}

			if((checking->xPos!=aroundMe.front()->xPos) || (checking->yPos!=aroundMe.front()->yPos) || (checking->zPos!=aroundMe.front()->yPos))
			{
				newSteps=checking->steps + 1.001;
			}
			else
			{
				newSteps=checking->steps + 1;
			}

			if(aroundMe.front()->lastPath==curPath)
			{
//				std::cout << "--- WE already added this path to the tocheck list" << std::endl;
			}

			if(canMove && (aroundMe.front()->lastPath!=curPath || aroundMe.front()->steps>newSteps))
			{
				aroundMe.front()->steps=newSteps;
				aroundMe.front()->lastStep=checking;

				if(aroundMe.front()->lastPath!=curPath)
				{
//					std::cout << "--- Added this path to the tocheck list" << std::endl;
					aroundMe.front()->lastPath=curPath;
					aroundMe.front()->estDist=heuristic(aroundMe.front()->xPos, aroundMe.front()->yPos, aroundMe.front()->zPos, targetX, targetY, targetZ);
					toCheck->push(aroundMe.front());
				}
				else
				{
					toCheck->update(aroundMe.front());
				}
			}
			else if(canMove)
			{
//				std::cout << "		It wasn't improved so no update..." << std::endl;
			}
			else
			{
//				std::cout << "		Couldn't move there" << std::endl;
			}
		}
	}

	std::cout << "path failed" << std::endl;
	return new Square(-666, -666, -666);
}

void World::go() {
	Sleep(1000);
/*
	for(int k=1;k<zMax-1;k++)
	{
		for(int j=1;j<yMax-1;j++)
		{
			for(int i=1;i<xMax-1;i++)
			{
				int spaces=0;
				for(int kk=1;kk<zMax-1;kk++)
				{
					for(int jj=1;jj<yMax-1;jj++)
					{
						for(int ii=1;ii<xMax-1;ii++)
						{
							Unit* guy=new Unit(0,0,0);

							if(guy->canMove(cube[i][j][k], cube[ii][jj][kk]))
							{
								spaces++;
								//std::cout << "Can move from " << i << " " << j << " " << k << " to " << ii << " " << jj << " " << kk << std::endl;
							}
						}
					}
				}

				if(spaces>0)
				{
					std::cout << "Can move from " << i << " " << j << " " << k << " to " << spaces << " different spots" << std::endl;
				}
			}
		}
	}

*/
	int timeTillPrint=0; // TODO: change this for when a player can be active?
	int turn=1;

	while(activeThings.size()!=0) // TODO: end game condition?
	{
		if(activeQueue.front()->initStatus==2)
		{
			activeThings.remove(activeQueue.front());
			activeQueue.pop();
			continue;
		}

		//std::cout << "guys: " << livingThings.size() << std::endl;
		//std::cout << "queues: " << livingQueue.size() << std::endl;

		Living* next=activeQueue.front();

		int wait=std::max(next->energy, 0); // Todo: if the queue system is perfect, this shouldn't be necessary
		//int ageing=std::max(wait,1); // this is, however; if multiple ppl go at the same time = 0 energy
		curTick+=wait;

		timeTillPrint-=wait;
		if(timeTillPrint<=0)
		{
			if(turn==13)
			{
				std::cout << "Debug stop" << std::endl;
			}

			print();
			std::cout << "Turn: " << turn << std::endl;
			turn++;
			timeTillPrint=1000;
			Sleep(delay);

			if(turn==30)
			{
				std::cout << "No problems, just pausing before the top gets cut off" << std::endl;
				pause();
			}
		}


	//	std::cout << "wait is " << wait << " on " << next->species << std::endl;
		for(std::list<Living*>::iterator thing=activeThings.begin(); thing!=activeThings.end(); thing++)
		{
		//	std::cout << "waiting on " << (*thing)->species << std::endl;
			(*thing)->energy-=wait;
		//	std::cout << "new nrg is " << (*thing)->energy << std::endl;
//			(*thing)->age(ageing);
		}

	//	std::cout << "             end waiting " << std::endl;

		activeQueue.pop();

		//curPath++;

		next->update();

		activeQueue.push(next);
	//	std::cout << "new things: " << livingThings.size() << std::endl;
	//	std::cout << "new queues: " << livingQueue.size() << std::endl;
	}

	print();
	std::cout << "Game over!" << std::endl;
	std::cout << "Turn: " << turn << std::endl;
	for(std::list<Item*>::iterator next=items.begin(); next!=items.end(); next++)
	{
		std::cout << ((*next)->owner!=NULL ? "ERROR " : "") << (*next)->name(2) << std::endl;
	}

	pause();
}

void World::stall() {
	Sleep(1000);
}

void World::pause() {
	std::cout << std::endl << "Paused, probably some stupid error."<< std::endl;
	std::cout << std::endl << "Derp"<< std::endl;

	std::string error;
	std::cin >> error;
}

void World::print() {
	for(int k=zMax-1;k>=0;k--)
	{
		for(int j=yMax-1;j>=0;j--)
		{
			for(int l=0;l<numLanes && k-l>=0;l++)
			{
				if(l!=0)
				{
					std::cout << "     ->     ";
				}

				for(int i=0;i<xMax;i++)
				{
					//if(!cube[i][j][k-l]->visible)
					//{
					//	std::cout << "?";
					//}
//					if(tryTargetTo(1, 1, 1, i, j, k-l, false, true)!=NULL)
//					{
//						std::cout << "?";
//					}
//					else if(tryTargetTo(i, j, k-l, 1, 1, 1, false, true)!=NULL)
//					{
//						std::cout << "!";
//					}
//					else if(tryTargetTo(1, 1, 1, i, j, k-l, true, true)!=NULL)
//					{
//						std::cout << " ";
//					}
//					if(tryTargetTo(i, j, k-l, 1, 1, 1, true, 1)==NULL && tryTargetTo(1, 1, 1, i, j, k-l, true, 1)!=NULL)
//					{
//						std::cout << "@";
//					}



					if(cube[i][j][k-l]->nogo)
					{
						std::cout << "#";
					}
					else if(!cube[i][j][k-l]->units.empty())
					{
						cube[i][j][k-l]->units.front()->print();
					}
					else if(!cube[i][j][k-l]->items.empty())
					{
						cube[i][j][k-l]->items.front()->print();
					}
					else if(cube[i][j][k-l]->block->center==3 && cube[i][j][k-l]->block->transparent)
					{
						std::cout << "W";
					}
					else if(cube[i][j][k-l]->block->center==3)
					{
						std::cout << "8";
					}
					else if(cube[i][j][k-l]->block->center==2)
					{
						std::cout << "Z";
					}
					else if(cube[i][j][k-l]->block->NotX>0)
					{
						std::cout << "<";
					}
					else if(cube[i][j][k-l]->block->NotX>0)
					{
						std::cout << ">";
					}
					else if(cube[i][j][k-l]->block->Y>0)
					{
						std::cout << "^";
					}
					else if(cube[i][j][k-l]->block->NotY>0)
					{
						std::cout << "v";
					}
					else if(cube[i][j][k-l]->block->center==1)
					{
						std::cout << ":";
					}
					else if(cube[i][j][k-l]->block->NotZ>0)
					{
						std::cout << "+";
					}
					else if(cube[i][j][k-l-1]->block->Z>0 || cube[i][j][k-l-1]->block->center>0)
					{
						std::cout << "-";
					}
					else
					{
						std::cout << " ";
					}
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		k-=numLanes-1;
	}
}
