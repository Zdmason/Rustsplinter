
#ifndef TASK_H_
#define TASK_H_

#include "../Actions/Action.h"

#include <iostream>

class Task {
public:
	Task();
	virtual ~Task();

	int id;

	std::string taskName;
	int priority;

	virtual bool attempt(Unit* taskMaster);
};

#endif /* TASK_H_ */
