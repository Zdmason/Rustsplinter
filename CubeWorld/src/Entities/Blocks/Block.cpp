
#include "Block.h"
#include "..\..\World.h"

Block::Block(int x, int y, int z) : Entity(x, y, z) {
	X=3;
	NotX=3;
	Y=3;
	NotY=3;
	Z=3;
	NotZ=3;
	center=3;
	transparent=false;

	hp=-1;
}

Block::~Block() {
	;
}

int Block::canMove(Square* here, Square* there) {
	if(there->nogo)
	{
		return there->block->id;
	}

	if(World::me->distance(here->xPos, here->yPos, here->zPos, there->xPos, there->yPos, there->zPos) >= 2)
	{
		std::cout << "Why is block " << name(2) << " trying to canFall more than one square away?";
		World::me->pause();
		return -666;
	}

	if(here->xPos+1==there->xPos && World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->species!="Empty") // if there is +x and non-empty
	{
		return World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->id;
	}
	else if(here->xPos-1==there->xPos && World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->species!="Empty") // if there is -x and non-empty
	{
		return World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->id;
	}
	else if(here->yPos+1==there->yPos && World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->species!="Empty") // if there is +y and non-empty
	{
		return World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->id;
	}
	else if(here->yPos-1==there->yPos && World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->species!="Empty") // if there is -y and non-empty
	{
		return World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->id;
	}
	else if(here->zPos+1==there->zPos && World::me->cube[here->xPos][here->yPos][here->zPos+1]->block->species!="Empty") // if there is +y and non-empty
	{
		return World::me->cube[here->xPos][here->yPos][here->zPos+1]->block->id;
	}
	else if(here->zPos-1==there->zPos && World::me->cube[here->xPos][here->yPos][here->zPos-1]->block->species!="Empty") // if there is -y and non-empty
	{
		return World::me->cube[here->xPos][here->yPos][here->zPos-1]->block->id;
	}

	if(!(there->block->species=="Empty"))
	{
		return there->block->id; //todo: do we care if we're moving into a solid block?
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

int Block::canPlanMove(Square* here, Square* there) {
	if(there->nogo)
	{
		return there->block->id;
	}

	if(World::me->distance(here->xPos, here->yPos, here->zPos, there->xPos, there->yPos, there->zPos) >= 2)
	{
		std::cout << "Why is block " << name(2) << " trying to canFall more than one square away?";
		World::me->pause();
		return -666;
	}

	if(here->xPos+1==there->xPos && World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->species!="Empty") // if there is +x and non-empty
	{
		return World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->id;
	}
	else if(here->xPos-1==there->xPos && World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->species!="Empty") // if there is -x and non-empty
	{
		return World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->id;
	}
	else if(here->yPos+1==there->yPos && World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->species!="Empty") // if there is +y and non-empty
	{
		return World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->id;
	}
	else if(here->yPos-1==there->yPos && World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->species!="Empty") // if there is -y and non-empty
	{
		return World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->id;
	}
	else if(here->zPos+1==there->zPos && World::me->cube[here->xPos][here->yPos][here->zPos+1]->block->species!="Empty") // if there is +y and non-empty
	{
		return World::me->cube[here->xPos][here->yPos][here->zPos+1]->block->id;
	}
	else if(here->zPos-1==there->zPos && World::me->cube[here->xPos][here->yPos][here->zPos-1]->block->species!="Empty") // if there is -y and non-empty
	{
		return World::me->cube[here->xPos][here->yPos][here->zPos-1]->block->id;
	}

	if(!(there->block->species=="Empty"))
	{
		return there->block->id; //todo: do we care if we're moving into a solid block?
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

void Block::damage(int impactHit, int slashHit, int stabHit, int brokeHit, int maxHit, int soulHit, Entity* cause, Entity* villain, bool canEmbed) {
	; // TODO: ignoring damage for now, add in when more block-related logic
}

void Block::tryDie() {
	std::cout << "[" << name(2) << " was de-blocked!] ";
	World::me->remBlock(this);
}
