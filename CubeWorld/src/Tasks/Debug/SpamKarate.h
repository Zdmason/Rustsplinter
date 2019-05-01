
#ifndef SPAMKARATE_H_
#define SPAMKARATE_H_

#include "../Task.h"

class SpamKarate : public Task {
public:
	SpamKarate();
	//~SpamKarate();

	bool attempt(Unit* taskMaster);
};

#endif /* SPAMKARATE_H_ */
