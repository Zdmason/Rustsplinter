
#ifndef SPAMMELEE_H_
#define SPAMMELEE_H_

#include "../Task.h"

class SpamMelee : public Task {
public:
	SpamMelee();
	//~SpamMelee();

	bool attempt(Unit* taskMaster);
};

#endif /* SPAMMELEE_H_ */
