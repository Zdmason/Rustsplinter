
#ifndef SPAMLEAP_H_
#define SPAMLEAP_H_

#include "../Task.h"

class SpamLeap : public Task {
public:
	SpamLeap();
	//~SpamLeap();

	bool attempt(Unit* taskMaster);
};

#endif /* SPAMLEAP_H_ */
