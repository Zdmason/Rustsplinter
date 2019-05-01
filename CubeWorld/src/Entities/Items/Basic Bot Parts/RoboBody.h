
#ifndef ROBOBODY_H_
#define ROBOBODY_H_

#include "../Item.h"

class RoboBody : public Item {
public:
	RoboBody(int x, int y, int z);
	//~RoboBody();

	void print();
};

#endif /* ROBOBODY_H_ */
