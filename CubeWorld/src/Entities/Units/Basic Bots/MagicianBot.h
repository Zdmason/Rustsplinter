
#ifndef MAGICIANBOT_H_
#define MAGICIANBOT_H_

#include "../Unit.h"

class MagicianBot : public Unit {
public:
	MagicianBot(int x, int y, int z);
	//~MagicianBot();

	void print();
};

#endif /* MAGICIANBOT_H_ */
