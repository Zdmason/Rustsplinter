
#include "Levitation.h"
#include "../../World.h"

Levitation::Levitation(int myDuration) : Status() {
	species="Levitation";
	isAlive=true;

	duoTags.push_back(LEVITATING);
	duration=myDuration;

	mahGrav=NULL;
}


void Levitation::clone(Entity* newVictim) {
	World::me->addStatus(new Levitation(duration), newVictim, true);
}


bool Levitation::letInfect(Status* effect) {
	return effect->species!=species;
}

void Levitation::onInfect()
{
	if(victim->myGrav==NULL)
	{
		victim->addGravForce(0, 0, 2000, NULL, NULL, false);
	}

	if(victim->myGrav!=NULL)
	{
		mahGrav=victim->myGrav;
		mahGrav->zAcl+=2000;
	}
	else
	{
		std::cout << "How the hell did we reach here at levitation? ";
		World::me->pause();
	}
}


bool Levitation::refresh() {
	if(victim->myGrav==NULL)
	{
		std::cout << "<Levitation's owner doesnt have a gravity anymore, correct?> ";
		return true;
	}

	if(victim->myGrav!=mahGrav)
	{
		if(mahGrav==NULL)
		{
			return true;
		}
		mahGrav->zAcl-=2000;
		mahGrav=victim->myGrav;
		mahGrav->zAcl+=2000;
		std::cout << "<Levitation caught an owner that switched gravity! did it work?> ";
		return false;
	}

	return true;
}


void Levitation::onDie()
{
	std::cout << "<Levitation died, adding back acceleration> ";
	if(victim->myGrav!=NULL && victim->myGrav==mahGrav)
	{
		std::cout << "IT WORKED BBY ";
		victim->myGrav->zAcl-=2000;
	}
	else
	{
		std::cout << "<VICTIM BETTER AINT HAVE GRAVITY> ";
		if(victim->myGrav!=NULL)
		{
			std::cout << "IT DOES ANYWAYS WTF?";
			World::me->pause();
		}
	}
}
