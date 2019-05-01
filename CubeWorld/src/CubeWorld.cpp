
#include "World.h"

#include <iostream>

int main() {
	std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!

	// 1-5 = grass blocks x high
	// 6-9 = cut stone x high
	// w = walker
	// d = drunkbot
	// s = skeleton
	// h = hello
	// f = frog
	// b = boxer
	// M = magician
	// z = zombie
	// S = slasher
	// A = armorbot
	// T = stabberbot
	// p = pickupbot
	// k = kidnapperbot
	// t = throwerbot
	// C = cowboybot



	std::string wurld[]= {
				"          ", // 1
				"          ",
				"          ",
				"          ",
				"          ", // 5
				"          ",
				"66666666  ",
				"   t   6  ",
				"       6  ",
				"   s   6  ", // 10
		};

	World galaxy=*(new World(12, 12, 3, wurld, 10, 3));



//	std::string wurld[]= {
//				"          ", // 1
//				"  5555555 ",
//				"555555555 ",
//				"  4444555 ",
//				"  3333555 ", // 5
//				"555222555 ",
//				"5555555555",
//				"5     k5 5",
//				"5 k k  555",
//				"5      5  ", // 10
//		};
//
//	World galaxy=*(new World(12, 12, 9, wurld, 10, 3));


//	std::string wurld[]= {
//				"          ", // 1
//				"          ",
//				"1     1   ",
//				"      1   ",
//				"          ", // 5
//				"      1   ",
//				"1     1   ",
//				" 1        ",
//				" 1    1   ",
//				" 1    1   ", // 10
//		};
//
//	World galaxy=*(new World(12, 12, 3, wurld, 10, 3));



//	std::string wurld[]= {
//				"                                                  ", // 1
//				"                                                  ",
//				"                                                  ",
//				"                                                  ",
//				"                                                  ", // 5
//				"                                                  ",
//				"                                                  ",
//				"                                                  ",
//				"                                                  ",
//				"                                                  ", // 10
//				"                                                  ",
//				"                                                  ",
//				"                                                  ",
//				"                                                  ",
//				"                                                  ", // 15
//				"                                                  ",
//				"                                                  ",
//				"                                                  ",
//				"                                                  ",
//				"                                                  ", // 20
//				"                                                  ",
//				"                                                  ",
//				"                                                  ",
//				"                                                  ",
//				"                                                  ", // 25
//				"                                                  ",
//				"                                                  ",
//				"                                                  ",
//				"                                                  ",
//				"                                                  ", // 30
//				"                                                  ",
//				"                                                  ",
//				"                                                  ",
//				"                                                  ",
//				"                                                  ", // 35
//				"                                6                 ",
//				"                                                  ",
//				"                                                  ",
//				"                                                  ",
//				"                                                  ", // 40
//				"         6                                        ",
//				"                                                  ",
//				"                                                  ",
//				"                                                  ",
//				"                                         6        ", // 45
//				"                                         6        ",
//				"                                         6        ",
//				"                                         6        ",
//				"                                                  ",
//				"                                                  " // 50
//		};
//	World galaxy=*(new World(50, 50, 4, wurld, 10, 4));


//	std::string wurld[]= {
//			"zzz", // 1
//			"zSz",
//			"z1z" // 5
//	};
//
//	World galaxy=*(new World(5, 5, 3, wurld, 10, 3));

	galaxy.print();

	galaxy.go();

	return 0;
}
