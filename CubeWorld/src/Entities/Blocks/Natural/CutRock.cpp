
#include "CutRock.h"

CutRock::CutRock(int x, int y, int z) : Block(x, y, z) {
	species="CutRock";

	hp=100;

	X=4;
	NotX=4;
	Y=4;
	NotY=4;
	Z=4;
	NotZ=4;
	center=3;
	transparent=false;
}

CutRock::~CutRock() {
	;
}
