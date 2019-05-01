
#ifndef TASKS_DEBUG_SPAMSHOOT_H_
#define TASKS_DEBUG_SPAMSHOOT_H_

#include "../Task.h"

class SpamShoot : public Task {
public:
	SpamShoot();
	//~SpamShoot();

	bool attempt(Unit* taskMaster);
};

#endif /* TASKS_DEBUG_SPAMSHOOT_H_ */
