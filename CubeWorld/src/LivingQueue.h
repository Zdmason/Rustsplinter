
#ifndef LIVINGQUEUE_H_
#define LIVINGQUEUE_H_

#include "Living.h"

#include <vector>

class LivingQueue {
public:
	LivingQueue();
	//~LivingQueue();

	std::vector<Living*> myVec;

	void push(Living* newLiving);
	void pop();
	Living* front();
	int size();
	void update(Living* oddLiving);
	void update();
};

#endif /* LIVINGQUEUE_H_ */
