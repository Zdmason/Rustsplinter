
#include "Nogo.h"

Nogo::Nogo(int x, int y, int z) : Block(x, y, z) {
	species="Nogo";

	hp=-1;

	X=3;
	NotX=3;
	Y=3;
	NotY=3;
	Z=3;
	NotZ=3;
	center=3;
	transparent=false;
}

Nogo::~Nogo() {
	;
}

void Nogo::damage(int impactHit, int slashHit, int stabHit, int brokeHit, int maxHit, int soulHit, Entity* cause, Entity* villain) {
	;
}
