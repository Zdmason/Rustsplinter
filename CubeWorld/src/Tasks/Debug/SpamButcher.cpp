
#include "SpamButcher.h"

#include "..\..\World.h"

SpamButcher::SpamButcher() : Task() {
	taskName="SpamButcher";
	priority=10;
}


bool SpamButcher::attempt(Unit* taskMaster) {
	Actool* butch=taskMaster->getActool("Butcher", NULL_ACTION_TAG, NULL_ACTION_SUBTAG, 2);

	if(butch==NULL)
	{
		std::cout << "{nuthin to butcher} ";
		return false;
	}

	std::cout << "{butchering something} ";
	return butch->startAttempt(NULL, butch->getITargets().front(), NULL);
}
