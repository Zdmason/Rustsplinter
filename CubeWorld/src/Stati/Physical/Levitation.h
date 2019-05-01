
#ifndef LEVITATION_H_
#define LEVITATION_H_

#include "../Status.h"
#include "../../Physics/Gravity.h"

class Levitation : public Status {
public:
	Levitation(int myDuration);
	//~Levitation();

	Gravity* mahGrav;

	void clone(Entity* newVictim);

	bool letInfect(Status* effect);
	void onInfect();

	bool refresh();

	void onDie();
};

#endif /* LEVITATION_H_ */
