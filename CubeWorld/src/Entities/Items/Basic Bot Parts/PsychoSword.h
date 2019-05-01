
#ifndef PSYCHOSWORD_H_
#define PSYCHOSWORD_H_

#include "../Item.h"

class PsychoSword : public Item {
public:
	PsychoSword(int x, int y, int z);
	//~PsychoSword();

	void print();
};

#endif /* PSYCHOSWORD_H_ */
