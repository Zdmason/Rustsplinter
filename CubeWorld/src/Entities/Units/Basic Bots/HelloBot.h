
#ifndef HELLOBOT_H_
#define HELLOBOT_H_

#include "../Unit.h"

class HelloBot : public Unit {
public:
	HelloBot(int x, int y, int z);
	//~HelloBot();

	void print();
};

#endif /* HELLOBOT_H_ */
