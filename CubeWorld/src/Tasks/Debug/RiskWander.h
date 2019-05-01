
#ifndef RISKWANDER_H_
#define RISKWANDER_H_

#include "../Task.h"

class RiskWander : public Task {
public:
	RiskWander();
	//~RiskWander();

	bool attempt(Unit* taskMaster);
};

#endif /* RISKWANDER_H_ */
