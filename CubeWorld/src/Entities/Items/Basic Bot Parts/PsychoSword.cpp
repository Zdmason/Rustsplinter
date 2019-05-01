
#include "PsychoSword.h"

#include "..\..\..\Actions\Attacks\Melee\MeleeAttack.h"

#include <iostream>

PsychoSword::PsychoSword(int x, int y, int z) : Item(x, y, z) {
	species="PsychoSword";

	maxHp=70;
	maxMaxHp=70;

	selfActions.push_back(new MeleeAttack("Slash", 0, 1000, 200, 0, 0, 0, 0, 0));
};

void PsychoSword::print() {
	std::cout << "A";
}
