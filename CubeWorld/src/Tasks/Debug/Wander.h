
#ifndef WANDER_H_
#define WANDER_H_

#include "../Task.h"

class Wander : public Task {
public:
	Wander();
	//~Wander();

	bool attempt(Unit* taskMaster);
};

#endif /* WANDER_H_ */
