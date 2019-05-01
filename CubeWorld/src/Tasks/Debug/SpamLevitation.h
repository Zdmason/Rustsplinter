
#ifndef SPAMLEVITATION_H_
#define SPAMLEVITATION_H_

#include "../Task.h"

class SpamLevitation : public Task {
public:
	SpamLevitation();
	//~SpamLevitation();

	bool attempt(Unit* taskMaster);
};

#endif /* SPAMLEVITATION_H_ */
