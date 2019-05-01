
#include "SpamStore.h"

#include "..\..\World.h"

SpamStore::SpamStore() : Task() {
	taskName="SpamStore";
	priority=1;
}


bool SpamStore::attempt(Unit* taskMaster) {
	Item* pack=taskMaster->getPart("RoboPack", NULL_ITEM_TAG, true, 0, 0, 0, NULL, 0, 0);
	if(pack==NULL)
	{
		std::cout << "{No robopack to store stuff into} ";
		return false;
	}

	Actool* storify=taskMaster->getActool("", STORE, NULL_ACTION_SUBTAG, NULL, pack, NULL);
	if(storify==NULL)
	{
		std::cout << "{Nothing to store into my " << pack->name(2) << "} ";
		return false;
	}

	std::cout << "{storing " << storify->tool->name(2) << "'s held " << storify->tool->holding->name(0) << " into " << pack->name(0) << "} ";
	return storify->startAttempt(NULL, pack, NULL);
}
