
#ifndef TASKS_DEBUG_SPAMSTORE_H_
#define TASKS_DEBUG_SPAMSTORE_H_

#include "../Task.h"

class SpamStore : public Task {
public:
	SpamStore();
	//~SpamStore();

	bool attempt(Unit* taskMaster);
};

#endif /* TASKS_DEBUG_SPAMSTORE_H_ */
