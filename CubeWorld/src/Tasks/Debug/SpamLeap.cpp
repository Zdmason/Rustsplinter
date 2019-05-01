
#include "SpamLeap.h"

#include "..\..\World.h"

SpamLeap::SpamLeap() : Task() {
	taskName="SpamLeap";
	priority=1;
}


bool SpamLeap::attempt(Unit* taskMaster) {
	Actool* LEEP=taskMaster->getActool("FrogLeap", NULL_ACTION_TAG, NULL_ACTION_SUBTAG, 2);
	if(LEEP==NULL)
	{
		std::cout << "{Cant leep if i'm unable to leepact} ";
		return false;
	}

	std::queue<Square*> around=World::me->getNear(taskMaster->xPos, taskMaster->yPos, taskMaster->zPos);
	std::vector<Square*> possible;
	while(!around.empty())
	{
		if(around.front()->zPos==taskMaster->zPos && taskMaster->canMove(World::me->cube[taskMaster->xPos][taskMaster->yPos][taskMaster->zPos], around.front())==0)
		{
			possible.push_back(around.front());
		}
		around.pop();
	}

	if(!possible.empty())
	{
		int choice=World::me->random(0, possible.size());

		int xDir=possible[choice]->xPos-taskMaster->xPos;
		int yDir=possible[choice]->yPos-taskMaster->yPos;

		std::cout << "{leeping around} ";
		LEEP->tryAttempt(taskMaster, NULL, NULL, World::me->cube[taskMaster->xPos+xDir][taskMaster->yPos+yDir][taskMaster->zPos]);
	}
	else
	{
		std::cout << "{leep upwards} ";
		LEEP->tryAttempt(taskMaster, NULL, NULL, World::me->cube[taskMaster->xPos][taskMaster->yPos][taskMaster->zPos+1]);
	}
	return true;
}
