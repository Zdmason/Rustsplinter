
#ifndef EMPTY_H_
#define EMPTY_H_

#include "../Block.h"

class Empty : public Block {
public:
	Empty(int x, int y, int z);
	~Empty();

	void damage(int impactHit, int slashHit, int stabHit, int brokeHit, int maxHit, int soulHit, Entity* cause, Entity* villain);
};

#endif /* EMPTY_H_ */
