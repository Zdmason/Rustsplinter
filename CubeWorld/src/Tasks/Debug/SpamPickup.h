
#ifndef TASKS_DEBUG_SPAMPICKUP_H_
#define TASKS_DEBUG_SPAMPICKUP_H_

#include "../Task.h"

class SpamPickup : public Task {
public:
	SpamPickup();
	//~SpamPickup();

	bool attempt(Unit* taskMaster);
};

#endif /* TASKS_DEBUG_SPAMPICKUP_H_ */
