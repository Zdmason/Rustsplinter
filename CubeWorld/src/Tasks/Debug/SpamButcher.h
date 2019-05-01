
#ifndef TASKS_DEBUG_SPAMBUTCHER_H_
#define TASKS_DEBUG_SPAMBUTCHER_H_

#include "../Task.h"

class SpamButcher : public Task {
public:
	SpamButcher();
	//~SpamButcher();

	bool attempt(Unit* taskMaster);
};

#endif /* TASKS_DEBUG_SPAMBUTCHER_H_ */
