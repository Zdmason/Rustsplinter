
#include "Empty.h"

Empty::Empty(int x, int y, int z) : Block(x, y, z) {
	species="Empty";

	hp=-1;

	X=0;
	NotX=0;
	Y=0;
	NotY=0;
	Z=0;
	NotZ=0;
	center=0;
	transparent=true;
}

Empty::~Empty() {
	;
}

void Empty::damage(int impactHit, int slashHit, int stabHit, int brokeHit, int maxHit, int soulHit, Entity* cause, Entity* villain) {
	;
}
