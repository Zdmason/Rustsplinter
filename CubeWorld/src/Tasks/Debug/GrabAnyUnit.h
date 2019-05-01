
#ifndef TASKS_DEBUG_GRABANYUNIT_H_
#define TASKS_DEBUG_GRABANYUNIT_H_

#include "../Task.h"

class GrabAnyUnit : public Task {
public:
	GrabAnyUnit();
	//~GrabAnyUnit();

	bool attempt(Unit* taskMaster);
};

#endif /* TASKS_DEBUG_GRABANYUNIT_H_ */
