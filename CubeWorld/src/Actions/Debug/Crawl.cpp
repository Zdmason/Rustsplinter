
#include "Crawl.h"
#include "..\..\World.h"

Crawl::Crawl() : MeleeMovement() {
	actionName="Crawl";

	castpoint=750;
	backswing=750;
}


int Crawl::howPossible(Item* tool, Unit* attempter) {
	if(tool==NULL || tool->initStatus==2)
	{
		return -1;
	}

	if(tool->selfTags.count(HANDLIKE)==0)
	{
		return -1;
	}

	if(!tool->isManipulatable(attempter))
	{
		return 0;
	}

	if(attempter->count("", HANDLIKE, true, 0, 0, 0, attempter, 0, 3)<2)
	{
		return 0;
	}

	if(getSTargets(tool, attempter).empty())
	{
		return 1;
	}

	return 2;
}


std::vector<Item*> Crawl::getTools(Unit* attempter, int possibleLevel) {
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
