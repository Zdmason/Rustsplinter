
#include "PsychoSpear.h"

#include "..\..\..\Actions\Attacks\Melee\MeleeAttack.h"

#include <iostream>

PsychoSpear::PsychoSpear(int x, int y, int z) : Item(x, y, z) {
	species="PsychoSpear";

	maxHp=70;
	maxMaxHp=70;

	selfActions.push_back(new MeleeAttack("Stab", 0, 0, 0, 1000, 200, 0, 0, 0));
};

void PsychoSpear::print() {
	std::cout << "Y";
}
