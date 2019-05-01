
#ifndef ROBOLEG_H_
#define ROBOLEG_H_

#include "../Item.h"

#include "../Archetypes/Leglike.h"

class RoboLeg : public Leglike {
public:
	RoboLeg(int x, int y, int z);
	//~RoboLeg();

	void print();
};

#endif /* ROBOLEG_H_ */
