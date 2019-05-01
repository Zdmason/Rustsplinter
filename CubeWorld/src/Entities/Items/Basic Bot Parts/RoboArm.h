
#ifndef ROBOARM_H_
#define ROBOARM_H_

#include "../Item.h"

#include "../Archetypes/Handlike.h"

class RoboArm : public Handlike {
public:
	RoboArm(int x, int y, int z);
	//~RoboArm();

	void print();
};

#endif /* ROBOARM_H_ */
