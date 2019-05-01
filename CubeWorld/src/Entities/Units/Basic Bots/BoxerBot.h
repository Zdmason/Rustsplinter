
#ifndef BOXERBOT_H_
#define BOXERBOT_H_

#include "../Unit.h"

class BoxerBot : public Unit {
public:
	BoxerBot(int x, int y, int z);
	//~BoxerBot();

	void print();
};

#endif /* BOXERBOT_H_ */
