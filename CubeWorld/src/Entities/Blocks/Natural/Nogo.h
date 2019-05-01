
#ifndef NOGO_H_
#define NOGO_H_

#include "../Block.h"

class Nogo : public Block {
public:
	Nogo(int x, int y, int z);
	~Nogo();

	void damage(int impactHit, int slashHit, int stabHit, int brokeHit, int maxHit, int soulHit, Entity* cause, Entity* villain);
};

#endif /* NOGO_H_ */
