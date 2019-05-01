
#ifndef GRASS_H_
#define GRASS_H_

#include "../Block.h"

class Grass : public Block {
public:
	Grass(int x, int y, int z);
	~Grass();
};

#endif /* GRASS_H_ */
