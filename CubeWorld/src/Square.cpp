
#include "Square.h"

#include "World.h"

Square::Square(int x, int y, int z) {
	xPos=x;
	yPos=y;
	zPos=z;

	nogo=false;
	block=NULL;

	lastPath=-1;
	steps=-1;
	estDist=-1;
	lastStep=NULL;

	if(x==0 || y==0 || z==0 || x==World::me->xMax-1 || y==World::me->yMax-1 || z==World::me->zMax-1)
	{
		nogo=true;
	}
}

void Square::refresh() {
	;
}

void Square::superRefresh() {
	refresh();

	std::queue<Square*> around=World::me->getNear(xPos, yPos, zPos);
	while(!around.empty())
	{
		around.front()->refresh();
		around.pop();
	}
}

Square* Square::initStep() {
	if(lastStep==NULL)
	{
		return NULL;
	}
	else if(lastStep->lastStep==NULL)
	{
		return this;
	}
	else
	{
		return lastStep->initStep();
	}
}

void Square::addUnit(Unit* thing) {
	units.push_back(thing);

	/*
	for(int i=0;i<=thing->size;i++)
	{
		sizeList[i]++;
	}
	*/
}

void Square::remUnit(Unit* thing) {
	units.remove(thing);

	/*
	for(int i=0;i<=thing->size;i++)
	{
		sizeList[i]--;
		if(sizeList[i]<0)
		{
			std::cout << "A unit moved out of my square, and now I have " << sizeList[i] << " size " << i << " things? : " << xPos << " " << yPos << " : " << thing->species;
			World::me->pause();
		}
	}
	*/
}

void Square::addItem(Item* obj) {
	items.push_back(obj);
}

void Square::remItem(Item* obj) {
	items.remove(obj);
}
