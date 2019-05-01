
#include "Butcher.h"

#include "../../World.h"

Butcher::Butcher() : Action() {
	actionName="Butcher";
}


int Butcher::howPossible(Item* tool, Unit* attempter) {
	if(tool==NULL)
	{
		return -1;
	}

	if(tool->initStatus==2)
	{
		return -2;
	}

	if(tool->selfTags.count(HANDLIKE)==0)
	{
		return -1;
	}

	if(tool->holding==NULL)
	{
		return 0;
	}

	if(!tool->isManipulatable(attempter))
	{
		return 0;
	}

	if(tool->holding->getBlob(1, 0, 0, 0, NULL, 0, 0).size()==1)
	{
		return 0;
	}

	return 2;
}


std::vector<Item*> Butcher::getTools(Unit* attempter, int possibleLevel) {
	std::vector<Item*> results;

	std::vector<Item*> maybeTools=attempter->getParts("", HANDLIKE, true, 0, 0, 0, NULL, 0, 0);
	for(unsigned int i=0;i<maybeTools.size();i++)
	{
		if(howPossible(maybeTools[i], attempter)>=possibleLevel)
		{
			results.push_back(maybeTools[i]);
		}
	}

	return results;
}

std::vector<Item*> Butcher::getITargets(Item* tool, Unit* attempter) {
	std::vector<Item*> result;

	result.push_back(tool->holding);

	return result;
}


bool Butcher::attempt(Item* tool, Unit* attempter, Unit* uTarget, Item* iTarget, Square* sTarget) {

	std::cout << " { Butchering my held " <<  tool->holding->name(0) << "} ";

	tool->holding->sever(NULL, true);

	return true;
}
