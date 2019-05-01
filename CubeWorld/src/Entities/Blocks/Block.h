
#ifndef BLOCK_H_
#define BLOCK_H_

#include "../Entity.h"

class Block : public Entity {
public:
	Block(int x, int y, int z);
	virtual ~Block();

	int X; // 0 = empty, 1 = ramp but passable, 2 = ramp but cant walk through, 3 = wall but not cornerblocking, 4 = solid / edgy
	int NotX;
	int Y;
	int NotY;
	int Z; // 0 = empty, 1 = standable and passable, 2 = wall but not cornerblocking, 3 = wall but not cornerblocking, 4 = solid / edgy
	int NotZ;
	int center; // 0 = empty, 1 = webby (only stay-able), 2 = ladder (standable / stayable / navigateable), 3 = solid
	bool transparent;

	int hp;

	int canMove(Square* here, Square* there);
	int canPlanMove(Square* here, Square* there);
	//int tryMove(int x, int y, int z);

	void damage(int impactHit, int slashHit, int stabHit, int brokeHit, int maxHit, int soulHit, Entity* cause, Entity* villain, bool canEmbed);

	void tryDie();
};

#endif /* BLOCK_H_ */
