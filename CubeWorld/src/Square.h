
#ifndef SQUARE_H_
#define SQUARE_H_

#include "Entities/Units/Unit.h"
#include "Entities/Blocks/Block.h"


#include <iostream>
#include <list>
#include <queue>
#include <set>

class Square {
public:
	Square(int x, int y, int z);

	int xPos, yPos, zPos;
	bool nogo; //TODO: remove when not needed

	Block* block;
	std::list<Unit*> units;
	std::list<Item*> items;

	//int sizeList[9];

	int lastPath;
	double steps;
	double estDist;
	Square* lastStep;

	Square* initStep();

	void refresh();
	void superRefresh();

	void addUnit(Unit* thing);
	void remUnit(Unit* thing);
	void addItem(Item* obj);
	void remItem(Item* obj);
	//void resize();
};

#endif /* SQUARE_H_ */
