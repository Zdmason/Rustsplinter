
#ifndef TASKS_DEBUG_SPAMTHROW_H_
#define TASKS_DEBUG_SPAMTHROW_H_

#include "../Task.h"

class SpamThrow : public Task {
public:
	SpamThrow();
	//~SpamThrow();

	bool attempt(Unit* taskMaster);
};

#endif /* TASKS_DEBUG_SPAMTHROW_H_ */
