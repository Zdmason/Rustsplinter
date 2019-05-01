
#include "Grass.h"

Grass::Grass(int x, int y, int z) : Block(x, y, z) {
	species="Grass";

	hp=100;

	X=2;
	NotX=2;
	Y=2;
	NotY=2;
	Z=2;
	NotZ=2;
	center=3;
	transparent=false;
}

Grass::~Grass() {
	;
}
