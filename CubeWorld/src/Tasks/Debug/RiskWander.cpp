
#include "RiskWander.h"
#include "..\..\World.h"

RiskWander::RiskWander() : Task() {
	taskName="RiskWander";
	priority=100;
}


bool RiskWander::attempt(Unit* taskMaster) {
	if(!taskMaster->letMove(-1, -1, -1, NULL))
	{
		std::cout << "{Not allowed to move for riskwandering} ";
		return false;
	}

	Actool* myMove=taskMaster->getActool("", MOVEMENT, NULL_ACTION_SUBTAG, 2);

	if(myMove==NULL)
	{
		std::cout << "{No moveacts for riskwandering} ";
		taskMaster->damage(0, 0, 0, 5, 0, 1, NULL, NULL, false);
		return false;
	}

	int randDest=World::me->random(0, myMove->getSTargets().size()-1);							// TODO: currently the same as wander, modify both when we get smart bools for act::getTarget
	if(myMove->startAttempt(NULL, NULL, myMove->getSTargets()[randDest]))
	{
		std::cout << " {Started riskwandering in the " << std::to_string(randDest) << " direction} ";
		taskMaster->damage(0, 0, 0, 5, 0, 1, NULL, NULL, false);
		return true;
	}

	std::cout << " {failed riskwandering in the " << std::to_string(randDest) << " direction???} ";
	return false;

//	std::queue<Square*> around=World::me->getNear(taskMaster->xPos, taskMaster->yPos, taskMaster->zPos);
//	while(!around.empty())
//	{
//		int rand=World::me->random(0, around.size()-1);
//
//		while(rand>0)
//		{
//			Square* skip=around.front();
//			around.pop();
//			around.push(skip);
//			rand--;
//		}
//
//		if(taskMaster->canRiskwalk(World::me->cube[taskMaster->xPos][taskMaster->yPos][taskMaster->zPos], around.front())==0)
//		{
//			int result=taskMaster->tryMove(around.front()->xPos, around.front()->yPos, around.front()->zPos, true, NULL, NULL);
//			if(result>=0)
//			{
//				std::cout << "{RiskWandered about} ";
//				taskMaster->damage(5, 0, CRUSH, 0, 1, NULL);
//				return true;
//			}
//			else
//			{
////				std::cout << "{but failed?} ";
//			}
//		}
//		around.pop();
//	}
//
//	std::cout << "{Couldn't riskwander about} ";
//	taskMaster->damage(5, 0, CRUSH, 0, 1, NULL);
//	return false;
}
