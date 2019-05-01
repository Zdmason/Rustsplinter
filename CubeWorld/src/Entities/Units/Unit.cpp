
#include "Unit.h"
#include "..\..\World.h"
//#include "..\..\Physics\Gravity.h"
#include "..\..\Actions\Attacks\MakeshiftAttack.h"
#include "..\..\Actions\Debug\Throw.h"

Unit::Unit(int x, int y, int z) : Entity(x, y, z) {
	order=UNIT;

//	team="None"; // TODO: modify this or constructor for multiple of the same type that are enemies? ie 2 warring goblin clans
	brain=NULL;
	staggerHp=0;
	painHp=0;
	soulHp=10;
//	sightRadius=0;
//	orders=NULL;
	// possibleCommands initialized as empty set
//	weapon=NULL;
	// possibleWeapons initialized as an empty set
	// holding initialized as an empty set

	activeActool=NULL;
	activeUTarget=NULL;
	activeITarget=NULL;
	activeSTarget=NULL;

	addedActions.push_back(new MakeshiftAttack());
	addedActions.push_back(new Throw());
}

Unit::~Unit() {
	; // TODO: make this / replace die()?
}


void Unit::update() {
	std::cout << name(1) << " (" << soulHp << " soulhp) : " << parts.size() << "(" << brain->getBlob(true, 3, 1, 3, NULL, 0, 0).size() << ") parts : ";

	if(energy!=0)
	{
		std::cout << "??? " << name(2) << " is updating even though my energy is " << energy << "???";
		World::me->pause();
	}

	energy=speed;

	worked=false;

	std::vector<Status*> afflictions(stati);
	for(unsigned int i=0;i<afflictions.size();i++)
	{
		afflictions[i]->subwork();
	}

	bool staggered=staggerHp>=100;
	staggerHp=(staggered ? staggerHp-100 : std::max(0, staggerHp-10));
	bool pained=painHp>=100;
	painHp=(pained ? painHp-100 : std::max(0, painHp-10));

	if(myGrav!=NULL)
	{
		std::cout << "Falling... " << std::endl;
		return;
	}
	else if(tags.count(STUNNED)!=0)
	{
		std::cout << "Stunned... " << std::endl;
		return;
	}
	else if(staggered)
	{
		std::cout << "Staggered... " << std::endl;
		return;
	}
	else if(pained)
	{
		std::cout << "Pained... " << std::endl;
		return;
	}
	else if(worked)
	{
		std::cout << "Already worked... " << std::endl;
		return;
	}

	if(activeActool!=NULL) // TODO: if stunned by any of the above, cancle actool or what?
	{
		Actool* temp=activeActool;
		Unit* tempU=activeUTarget;
		Item* tempI=activeITarget;
		Square* tempS=activeSTarget;

		activeActool=NULL;
		activeUTarget=NULL;
		activeITarget=NULL;
		activeSTarget=NULL;

		if(temp->tryAttempt(tempU, tempI, tempS, true))
		{
			std::cout << " (act " << temp->act->actionName << " subcompleted!) " << std::endl;
			return;
		}
		else
		{
			std::cout << " (task subfailed!) " << std::endl;
		}
	}


	if(getActool("", NULL_ACTION_TAG, NULL_ACTION_SUBTAG, 2)==NULL)
	{
		std::cout << "{no possible actions!} ";
	}

	std::vector<Task*> taskList=getTasks("");

	if(taskList.empty())
	{
		std::cout << "{no tasks at all. Probably error?} ";
		World::me->pause();
	}

	for(unsigned int i=0; i<taskList.size(); i++)
	{
		if(taskList[i]->attempt(this))
		{
			std::cout << std::endl;
			return;
		}
	}

	std::cout << "No tasks to do, so I died by 10 inside. ";
	damage(0, 0, 0, 10, 0, 1, NULL, NULL, false);
	energy=speed;

	std::cout << std::endl;
}

void Unit::work() {
	std::cout << "No tasks to do, so I died a lot inside. ";
	damage(0, 0, 0, 10, 0, 0, NULL, NULL, false);
}


int Unit::canWalk(Square* here, Square* there) {
	// Returns: -3 = couldn't start / end on square, -2 = couldn't letMove, -1 = same square, 0 = canMove, 1+ = id of blocking entity

	if(here->xPos==there->xPos && here->yPos==there->yPos && here->zPos==there->zPos)
	{
		return -1;
	}

	// More than 1 square away
	if(World::me->distance(here->xPos, here->yPos, here->zPos, there->xPos, there->yPos, there->zPos) >= 2)
	{
		std::cout << "Why is unit " << name(2) << " trying to canWalk more than one square away?";
		World::me->pause();
		return -666;
	}

	// Not starting on stable ground
	if(here->block->NotZ==0 &&
		here->block->center==0 &&
		World::me->cube[here->xPos][here->yPos][here->zPos-1]->block->Z==0 &&
		World::me->cube[here->xPos][here->yPos][here->zPos-1]->block->center<2)
	{
		return -3;
	}

	// Not ending on stable ground
	if(there->block->NotZ==0 &&
		there->block->center==0 &&
		World::me->cube[there->xPos][there->yPos][there->zPos-1]->block->Z==0 &&
		World::me->cube[there->xPos][there->yPos][there->zPos-1]->block->center<3)
	{
		return -3;
	}

	int minBlocking=0;

	int xMove=0;
	if(here->xPos > there->xPos)
	{
		xMove=-1;
		minBlocking++;
	}
	else if(here->xPos < there->xPos)
	{
		xMove=1;
		minBlocking++;
	}

	int yMove=0;
	if(here->yPos > there->yPos)
	{
		yMove=-1;
		minBlocking++;
	}
	else if(here->yPos < there->yPos)
	{
		yMove=1;
		minBlocking++;
	}

	int zMove=0;
	if(here->zPos > there->zPos)
	{
		zMove=-1;
		minBlocking++;
	}
	else if(here->zPos < there->zPos)
	{
		zMove=1;
		minBlocking++;
	}

	if(minBlocking==0)
	{
		std::cout << "Why is item " << name(2) << " failing hard at minBlocking?";
		World::me->pause();
		return -666;
	}
	else if(minBlocking==1)
	{
		minBlocking=2;
	}
	else
	{
		minBlocking=4;
	}

	for(int i=std::min(0, xMove); i<=std::max(0, xMove);i++)
	{
		for(int j=std::min(0, yMove); j<=std::max(0, yMove);j++)
		{
			for(int k=std::min(0, zMove); k<=std::max(0, zMove);k++)
			{
				if(xMove!=0)
				{
					if(i==std::min(0, xMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->X>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
					else if(i==std::max(0, xMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->NotX>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
				}

				if(yMove!=0)
				{
					if(j==std::min(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->Y>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
					else if(j==std::max(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->NotY>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
				}

				if(zMove!=0)
				{
					if(k==std::min(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->Z>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
					else if(k==std::max(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->NotZ>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
				}
			}
		}
	}

	if(zMove==1) // If we're movin up
	{
		if(xMove==0 && yMove==0)
		{
			if(here->block->center==0) // Can't climb directly up if not stayable
			{
				return -3;
			}
		}
		else if(xMove!=0 && yMove!=0)
		{
			if(xMove==1 && yMove==1)
			{
				// Check right side for a ramp up
				if(here->block->X!=1 && here->block->X!=2 &&
					World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->NotX!=1 && World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->NotX!=2 &&
					World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->Y!=1 && World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->Y!=2 &&
					World::me->cube[here->xPos+1][here->yPos+1][here->zPos]->block->NotY!=1 && World::me->cube[here->xPos+1][here->yPos+1][here->zPos]->block->NotY!=2)
				{
					return -3;
				}
				// Check left side for a ramp up
				else if(here->block->Y!=1 && here->block->Y!=2 &&
					World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->NotY!=1 && World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->NotY!=2 &&
					World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->X!=1 && World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->X!=2 &&
					World::me->cube[here->xPos+1][here->yPos+1][here->zPos]->block->NotX!=1 && World::me->cube[here->xPos+1][here->yPos+1][here->zPos]->block->NotX!=2)
				{
					return -3;
				}
			}
			else if(xMove==1 && yMove==-1)
			{
				if(here->block->X!=1 && here->block->X!=2 &&
					World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->NotX!=1 && World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->NotX!=2 &&
					World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->NotY!=1 && World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->NotY!=2 &&
					World::me->cube[here->xPos+1][here->yPos-1][here->zPos]->block->NotY!=1 && World::me->cube[here->xPos+1][here->yPos-1][here->zPos]->block->NotY!=2)
				{
					return -3;
				}
				else if(here->block->NotY!=1 && here->block->NotY!=2 &&
					World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->Y!=1 && World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->Y!=2 &&
					World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->X!=1 && World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->X!=2 &&
					World::me->cube[here->xPos+1][here->yPos-1][here->zPos]->block->NotX!=1 && World::me->cube[here->xPos+1][here->yPos-1][here->zPos]->block->NotX!=2)
				{
					return -3;
				}
			}
			else if(xMove==-1 && yMove==1)
			{
				if(here->block->NotX!=1 && here->block->NotX!=2 &&
					World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->X!=1 && World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->X!=2 &&
					World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->Y!=1 && World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->Y!=2 &&
					World::me->cube[here->xPos-1][here->yPos+1][here->zPos]->block->NotY!=1 && World::me->cube[here->xPos-1][here->yPos+1][here->zPos]->block->NotY!=2)
				{
					return -3;
				}
				else if(here->block->Y!=1 && here->block->Y!=2 &&
					World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->NotY!=1 && World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->NotY!=2 &&
					World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->NotX!=1 && World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->NotX!=2 &&
					World::me->cube[here->xPos-1][here->yPos+1][here->zPos]->block->X!=1 && World::me->cube[here->xPos-1][here->yPos+1][here->zPos]->block->X!=2)
				{
					return -3;
				}
			}
			else if(xMove==-1 && yMove==-1)
			{
				if(here->block->NotX!=1 && here->block->NotX!=2 &&
					World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->X!=1 && World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->X!=2 &&
					World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->NotY!=1 && World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->NotY!=2 &&
					World::me->cube[here->xPos-1][here->yPos-1][here->zPos]->block->Y!=1 && World::me->cube[here->xPos-1][here->yPos-1][here->zPos]->block->Y!=2)
				{
					return -3;
				}
				else if(here->block->NotY!=1 && here->block->NotY!=2 &&
					World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->Y!=1 && World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->Y!=2 &&
					World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->NotX!=1 && World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->NotX!=2 &&
					World::me->cube[here->xPos-1][here->yPos-1][here->zPos]->block->X!=1 && World::me->cube[here->xPos-1][here->yPos-1][here->zPos]->block->X!=2)
				{
					return -3;
				}
			}
			else
			{
				std::cout << "How did we reach this failpart at z+ canWalk?";
				World::me->pause();
				return -666;
			}
		}
		else if(xMove==1)
		{
			if(here->block->X!=1 && here->block->X!=2 &&
				World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->NotX!=1 && World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->NotX!=2)
			{
				return -3;
			}
		}
		else if(xMove==-1)
		{
			if(here->block->NotX!=1 && here->block->NotX!=2 &&
				World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->X!=1 && World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->X!=2)
			{
				return -3;
			}
		}
		else if(yMove==1)
		{
			if(here->block->Y!=1 && here->block->Y!=2 &&
				World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->NotY!=1 && World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->NotY!=2)
			{
				return -3;
			}
		}
		else if(yMove==-1)
		{
			if(here->block->NotY!=1 && here->block->NotY!=2 &&
				World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->Y!=1 && World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->Y!=2)
			{
				return -3;
			}
		}
		else
		{
			std::cout << "How did we reach this SUPER failpart at z+ canWalk?";
			World::me->pause();
		}
	}
	else if(zMove==-1) // If we're movin down
	{
		if(xMove==0 && yMove==0)
		{
			if(there->block->center==0) // Can't climb up if no ladder / stairs
			{
				return -3;
			}
		}
		else if(xMove!=0 && yMove!=0)
		{
			if(xMove==-1 && yMove==-1)
			{
				if(there->block->X!=1 && there->block->X!=2 &&
					World::me->cube[there->xPos+1][there->yPos][there->zPos]->block->NotX!=1 && World::me->cube[there->xPos+1][there->yPos][there->zPos]->block->NotX!=2 &&
					World::me->cube[there->xPos+1][there->yPos][there->zPos]->block->Y!=1 && World::me->cube[there->xPos+1][there->yPos][there->zPos]->block->Y!=2 &&
					World::me->cube[there->xPos+1][there->yPos+1][there->zPos]->block->NotY!=1 && World::me->cube[there->xPos+1][there->yPos+1][there->zPos]->block->NotY!=2)
				{
					return -3;
				}
				else if(there->block->Y!=1 && there->block->Y!=2 &&
					World::me->cube[there->xPos][there->yPos+1][there->zPos]->block->NotY!=1 && World::me->cube[there->xPos][there->yPos+1][there->zPos]->block->NotY!=2 &&
					World::me->cube[there->xPos][there->yPos+1][there->zPos]->block->X!=1 && World::me->cube[there->xPos][there->yPos+1][there->zPos]->block->X!=2 &&
					World::me->cube[there->xPos+1][there->yPos+1][there->zPos]->block->NotX!=1 && World::me->cube[there->xPos+1][there->yPos+1][there->zPos]->block->NotX!=2)
				{
					return -3;
				}
			}
			else if(xMove==-1 && yMove==1)
			{
				if(there->block->X!=1 && there->block->X!=2 &&
					World::me->cube[there->xPos+1][there->yPos][there->zPos]->block->NotX!=1 && World::me->cube[there->xPos+1][there->yPos][there->zPos]->block->NotX!=2 &&
					World::me->cube[there->xPos+1][there->yPos][there->zPos]->block->NotY!=1 && World::me->cube[there->xPos+1][there->yPos][there->zPos]->block->NotY!=2 &&
					World::me->cube[there->xPos+1][there->yPos-1][there->zPos]->block->NotY!=1 && World::me->cube[there->xPos+1][there->yPos-1][there->zPos]->block->NotY!=2)
				{
					return -3;
				}
				else if(there->block->NotY!=1 && there->block->NotY!=2 &&
					World::me->cube[there->xPos][there->yPos-1][there->zPos]->block->Y!=1 && World::me->cube[there->xPos][there->yPos-1][there->zPos]->block->Y!=2 &&
					World::me->cube[there->xPos][there->yPos-1][there->zPos]->block->X!=1 && World::me->cube[there->xPos][there->yPos-1][there->zPos]->block->X!=2 &&
					World::me->cube[there->xPos+1][there->yPos-1][there->zPos]->block->NotX!=1 && World::me->cube[there->xPos+1][there->yPos-1][there->zPos]->block->NotX!=2)
				{
					return -3;
				}
			}
			else if(xMove==1 && yMove==-1)
			{
				if(there->block->NotX!=1 && there->block->NotX!=2 &&
					World::me->cube[there->xPos-1][there->yPos][there->zPos]->block->X!=1 && World::me->cube[there->xPos-1][there->yPos][there->zPos]->block->X!=2 &&
					World::me->cube[there->xPos-1][there->yPos][there->zPos]->block->Y!=1 && World::me->cube[there->xPos-1][there->yPos][there->zPos]->block->Y!=2 &&
					World::me->cube[there->xPos-1][there->yPos+1][there->zPos]->block->NotY!=1 && World::me->cube[there->xPos-1][there->yPos+1][there->zPos]->block->NotY!=2)
				{
					return -3;
				}
				else if(there->block->Y!=1 && there->block->Y!=2 &&
					World::me->cube[there->xPos][there->yPos+1][there->zPos]->block->NotY!=1 && World::me->cube[there->xPos][there->yPos+1][there->zPos]->block->NotY!=2 &&
					World::me->cube[there->xPos][there->yPos+1][there->zPos]->block->NotX!=1 && World::me->cube[there->xPos][there->yPos+1][there->zPos]->block->NotX!=2 &&
					World::me->cube[there->xPos-1][there->yPos+1][there->zPos]->block->X!=1 && World::me->cube[there->xPos-1][there->yPos+1][there->zPos]->block->X!=2)
				{
					return -3;
				}
			}
			else if(xMove==1 && yMove==1)
			{
				if(there->block->NotX!=1 && there->block->NotX!=2 &&
					World::me->cube[there->xPos-1][there->yPos][there->zPos]->block->X!=1 && World::me->cube[there->xPos-1][there->yPos][there->zPos]->block->X!=2 &&
					World::me->cube[there->xPos-1][there->yPos][there->zPos]->block->NotY!=1 && World::me->cube[there->xPos-1][there->yPos][there->zPos]->block->NotY!=2 &&
					World::me->cube[there->xPos-1][there->yPos-1][there->zPos]->block->Y!=1 && World::me->cube[there->xPos-1][there->yPos-1][there->zPos]->block->Y!=2)
				{
					return -3;
				}
				else if(there->block->NotY!=1 && there->block->NotY!=2 &&
					World::me->cube[there->xPos][there->yPos-1][there->zPos]->block->Y!=1 && World::me->cube[there->xPos][there->yPos-1][there->zPos]->block->Y!=2 &&
					World::me->cube[there->xPos][there->yPos-1][there->zPos]->block->NotX!=1 && World::me->cube[there->xPos][there->yPos-1][there->zPos]->block->NotX!=2 &&
					World::me->cube[there->xPos-1][there->yPos-1][there->zPos]->block->X!=1 && World::me->cube[there->xPos-1][there->yPos-1][there->zPos]->block->X!=2)
				{
					return -3;
				}
			}
			else
			{
				std::cout << "How did we reach this failpart at z- canWalk?";
				World::me->pause();
			}
		}
		else if(xMove==-1)
		{
			if(there->block->X!=1 && there->block->X!=2 &&
				World::me->cube[there->xPos+1][there->yPos][there->zPos]->block->NotX!=1 && World::me->cube[there->xPos+1][there->yPos][there->zPos]->block->NotX!=2)
			{
				return -3;
			}
		}
		else if(xMove==1)
		{
			if(there->block->NotX!=1 && there->block->NotX!=2 &&
				World::me->cube[there->xPos-1][there->yPos][there->zPos]->block->X!=1 && World::me->cube[there->xPos-1][there->yPos][there->zPos]->block->X!=2)
			{
				return -3;
			}
		}
		else if(yMove==-1)
		{
			if(there->block->Y!=1 && there->block->Y!=2 &&
				World::me->cube[there->xPos][there->yPos+1][there->zPos]->block->NotY!=1 && World::me->cube[there->xPos][there->yPos+1][there->zPos]->block->NotY!=2)
			{
				return -3;
			}
		}
		else if(yMove==1)
		{
			if(there->block->NotY!=1 && there->block->NotY!=2 &&
				World::me->cube[there->xPos][there->yPos-1][there->zPos]->block->Y!=1 && World::me->cube[there->xPos][there->yPos-1][there->zPos]->block->Y!=2)
			{
				return -3;
			}
		}
		else
		{
			std::cout << "How did we reach this SUPER failpart at z- canWalk?";
			World::me->pause();
		}
	}

	if(there->block->center==3)
	{
		return there->block->id; //todo: do we also care if we're moving from inside a solid block? add in when phasing is in
	}

	if(there->block->species!="Empty")
	{
		std::cout << "We're trying to walk into one of these, but we missed all the checks before rturning 0? " << there->block->name(2);
		World::me->pause();
		return -666;
	}

	// Walking onto map edge
	if(there->nogo)
	{
		std::cout << "We're trying to walk onto a map edge, but we didn't get stopped before this final check? " << there->block->name(2);
		World::me->pause();
		return -3;
	}

	return 0;

	/*
	if(there->nogo)
	{
		return there->center;
	}

	if(World::me->distance(here->xPos, here->yPos, here->zPos, there->xPos, there->yPos, there->zPos) >= 2)
	{
		std::cout << "Why is unit " << species << " trying to canWalk more than one square away?";
		World::me->pause();
		return new Block(-1, -1, -1);
	}

	if(!here->center->platform && !World::me->cube[here->xPos][here->yPos][here->zPos-1]->center->standable)
	{
		return new Block(-1, -1, -1); //TODO: do we care if we're starting on air?
	}

	if(!there->center->platform && !World::me->cube[there->xPos][there->yPos][there->zPos-1]->center->standable)
	{
		return new Block(-1, -1, -1); // Can't walk onto open air
	}

	if(here->zPos+1==there->zPos) // if there is +z
	{
		if(here->xPos==there->xPos && here->yPos==there->yPos) // directly +z
		{
			if(!here->center->stairs)
			{
				return new Block(-1, -1, -1); // Can't walk directly up without stairs
			}
		}
		else if(World::me->cube[here->xPos][here->yPos][here->zPos+1]->center->edgy)
		{
			return World::me->cube[here->xPos][here->yPos][here->zPos+1]->center; // Block above here is edgy = blocking
		}
		else if(World::me->cube[there->xPos][there->yPos][there->zPos-1]->center->edgy)
		{
			return World::me->cube[there->xPos][there->yPos][there->zPos-1]->center; // Block below there is edgy = blocking
		}
		else if(!World::me->cube[there->xPos][there->yPos][there->zPos-1]->center->ramp)
		{
			return new Block(-1, -1, -1); // Block below there isn't a ramp = can't climb up
		}
		else if(here->xPos!=there->xPos && here->yPos!=there->yPos)
		{
			int xMove=-1;
			if(here->xPos+1==there->xPos)
			{
				xMove=1;
			}

			int yMove=-1;
			if(here->yPos+1==there->yPos)
			{
				yMove=1;
			}

			if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center->edgy)
			{
				return World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center; // lower x side is edgy = blocking
			}

			if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center->edgy)
			{
				return World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center; // lower y side is edgy = blocking
			}

			if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos+1]->center->edgy)
			{
				return World::me->cube[here->xPos+xMove][here->yPos][here->zPos+1]->center; // upper x side is edgy = blocking
			}

			if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos+1]->center->edgy)
			{
				return World::me->cube[here->xPos][here->yPos+yMove][here->zPos+1]->center; // upper y side is edgy = blocking
			}
		}
	}
	else if(here->zPos-1==there->zPos) // if there is -z
	{
		if(here->xPos==there->xPos && here->yPos==there->yPos) // directly -z
		{
			if(!there->center->stairs)
			{
				return new Block(-1, -1, -1); // Can't walk directly down without stairs
			}
		}
		else if(World::me->cube[there->xPos][there->yPos][there->zPos+1]->center->edgy)
		{
			return World::me->cube[there->xPos][there->yPos][there->zPos+1]->center; // Block above there is edgy = blocking
		}
		else if(World::me->cube[here->xPos][here->yPos][here->zPos-1]->center->edgy)
		{
			return World::me->cube[here->xPos][here->yPos][here->zPos-1]->center; // Block below here is edgy = blocking
		}
		else if(World::me->cube[here->xPos][here->yPos][here->zPos-1]->center->ramp)
		{
			return new Block(-1, -1, -1); // Block below here isn't a ramp = can't climb back up
		}
		else if(here->xPos!=there->xPos && here->yPos!=there->yPos)
		{
			int xMove=-1;
			if(here->xPos+1==there->xPos)
			{
				xMove=1;
			}

			int yMove=-1;
			if(here->yPos+1==there->yPos)
			{
				yMove=1;
			}

			if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center->edgy)
			{
				return World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center; // upper x side is edgy = blocking
			}

			if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center->edgy)
			{
				return World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center; // upper y side is edgy = blocking
			}

			if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos-1]->center->edgy)
			{
				return World::me->cube[here->xPos+xMove][here->yPos][here->zPos-1]->center; // x side is edgy = blocking
			}

			if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos-1]->center->edgy)
			{
				return World::me->cube[here->xPos][here->yPos+yMove][here->zPos-1]->center; // y side is edgy = blocking
			}
		}
	}
	else if(here->xPos!=there->xPos && here->yPos!=there->yPos)
	{
		int xMove=-1;
		if(here->xPos+1==there->xPos)
		{
			xMove=1;
		} //TODO: can math this shorter somehow?

		int yMove=-1;
		if(here->yPos+1==there->yPos)
		{
			yMove=1;
		}

		if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center->edgy)
		{
			return World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center; // x side is edgy = blocking
		}

		if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center->edgy)
		{
			return World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center; // y side is edgy = blocking
		}
	}

	if(!there->center->passable)
	{
		return there->center;
	}

	return NULL;
*/

//	  #'s 	Sizes			is blocked by (at least)
//	 -------------------------------------------
//	   0   	ghosts  		sealed
//	   1   	flying / gas  	solid walls
//	   2   	tiny / items  	buildings
//	   3   	small  			huge / enemy small
//	   4   	medium  		medium / enemy small
//	   5   	huge 			small
//	   6  	building		tiny / items
//	   7   	solid wall		flying / gas
//	   8   	sealed	 		anything

	/*
	std::list<Unit*>::iterator thing;
	if(place->units.empty())
	{
		return true;
	}
	else if(place->sizeList[8]!=0)
	{
		return false;
	}
	else if(size==0 || tags.count(PHASING)!=0)
	{
		//TODO: is this true?
		return true;
	}
	else if(!visible || place->viewers.count(this)==0)
	{
		return place->sizeList[6]==0;
	}
	else if(size==1 || tags.count(FLYING)!=0)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if(((*thing)->size>=6 && (*thing)->tags.count(PHASING)==0 && (*thing)->visible))
			{
				return false;
			}
		}

		return true;
	}
	else if(size==2)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if(((*thing)->size>=5 && (*thing)->tags.count(PHASING)==0 && (*thing)->visible))
			{
				return false;
			}
		}

		return true;
	}
	else if(size==3)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->tags.count(PHASING)==0 && ((*thing)->size>=6 || ((*thing)->visible && ((*thing)->size>=5 || ((*thing)->size>=3 && (*thing)->team!=team)))))
			{
				return false;
			}
		}

		return true;
	}
	else if(size==4)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->tags.count(PHASING)==0 && ((*thing)->size>=6 || ((*thing)->visible && ((*thing)->size>=4 || ((*thing)->size>=3 && (*thing)->team!=team)))))
			{
				return false;
			}
		}

		return true;
	}
	else if(size==5)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->tags.count(PHASING)==0 && ((*thing)->size>=6 || ((*thing)->visible && (*thing)->size>=3)))
			{
				return false;
			}
		}

		return true;
	}

	return false;
	*/
}

int Unit::canRiskwalk(Square* here, Square* there) {
	// Returns: -3 = couldn't start / end on square, -2 = couldn't letMove, -1 = same square, 0 = canMove, 1+ = id of blocking entity

	if(here->xPos==there->xPos && here->yPos==there->yPos && here->zPos==there->zPos)
	{
		return -1;
	}

	// More than 1 square away
	if(World::me->distance(here->xPos, here->yPos, here->zPos, there->xPos, there->yPos, there->zPos) >= 2)
	{
		std::cout << "Why is unit " << name(2) << " trying to canRiskWalk more than one square away?";
		World::me->pause();
		return -666;
	}

	// Not starting on stable ground
	if(here->block->NotZ==0 &&
		here->block->center==0 &&
		World::me->cube[here->xPos][here->yPos][here->zPos-1]->block->Z==0 &&
		World::me->cube[here->xPos][here->yPos][here->zPos-1]->block->center<2)
	{
		return -3;
	}

	int minBlocking=0;

	int xMove=0;
	if(here->xPos > there->xPos)
	{
		xMove=-1;
		minBlocking++;
	}
	else if(here->xPos < there->xPos)
	{
		xMove=1;
		minBlocking++;
	}

	int yMove=0;
	if(here->yPos > there->yPos)
	{
		yMove=-1;
		minBlocking++;
	}
	else if(here->yPos < there->yPos)
	{
		yMove=1;
		minBlocking++;
	}

	int zMove=0;
	if(here->zPos > there->zPos)
	{
		zMove=-1;
		minBlocking++;
	}
	else if(here->zPos < there->zPos)
	{
		zMove=1;
		minBlocking++;
	}

	if(minBlocking==0)
	{
		std::cout << "Why is item " << name(2) << " failing hard at riskwalk minBlocking?";
		World::me->pause();
		return -666;
	}
	else if(minBlocking==1)
	{
		minBlocking=2;
	}
	else
	{
		minBlocking=4;
	}

	for(int i=std::min(0, xMove); i<=std::max(0, xMove);i++)
	{
		for(int j=std::min(0, yMove); j<=std::max(0, yMove);j++)
		{
			for(int k=std::min(0, zMove); k<=std::max(0, zMove);k++)
			{
				if(xMove!=0)
				{
					if(i==std::min(0, xMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->X>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
					else if(i==std::max(0, xMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->NotX>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
				}

				if(yMove!=0)
				{
					if(j==std::min(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->Y>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
					else if(j==std::max(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->NotY>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
				}

				if(zMove!=0)
				{
					if(k==std::min(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->Z>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
					else if(k==std::max(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->NotZ>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
				}
			}
		}
	}

	if(zMove==1) // If we're movin up
	{
		if(xMove==0 && yMove==0)
		{
			if(here->block->center==0) // Can't climb directly up if not stayable
			{
				return -3;
			}
		}
		else if(xMove!=0 && yMove!=0)
		{
			if(xMove==1 && yMove==1)
			{
				// Check right side for a ramp up
				if(here->block->X!=1 && here->block->X!=2 &&
					World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->NotX!=1 && World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->NotX!=2 &&
					World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->Y!=1 && World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->Y!=2 &&
					World::me->cube[here->xPos+1][here->yPos+1][here->zPos]->block->NotY!=1 && World::me->cube[here->xPos+1][here->yPos+1][here->zPos]->block->NotY!=2)
				{
					return -3;
				}
				// Check left side for a ramp up
				else if(here->block->Y!=1 && here->block->Y!=2 &&
					World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->NotY!=1 && World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->NotY!=2 &&
					World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->X!=1 && World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->X!=2 &&
					World::me->cube[here->xPos+1][here->yPos+1][here->zPos]->block->NotX!=1 && World::me->cube[here->xPos+1][here->yPos+1][here->zPos]->block->NotX!=2)
				{
					return -3;
				}
			}
			else if(xMove==1 && yMove==-1)
			{
				if(here->block->X!=1 && here->block->X!=2 &&
					World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->NotX!=1 && World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->NotX!=2 &&
					World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->NotY!=1 && World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->NotY!=2 &&
					World::me->cube[here->xPos+1][here->yPos-1][here->zPos]->block->NotY!=1 && World::me->cube[here->xPos+1][here->yPos-1][here->zPos]->block->NotY!=2)
				{
					return -3;
				}
				else if(here->block->NotY!=1 && here->block->NotY!=2 &&
					World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->Y!=1 && World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->Y!=2 &&
					World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->X!=1 && World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->X!=2 &&
					World::me->cube[here->xPos+1][here->yPos-1][here->zPos]->block->NotX!=1 && World::me->cube[here->xPos+1][here->yPos-1][here->zPos]->block->NotX!=2)
				{
					return -3;
				}
			}
			else if(xMove==-1 && yMove==1)
			{
				if(here->block->NotX!=1 && here->block->NotX!=2 &&
					World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->X!=1 && World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->X!=2 &&
					World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->Y!=1 && World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->Y!=2 &&
					World::me->cube[here->xPos-1][here->yPos+1][here->zPos]->block->NotY!=1 && World::me->cube[here->xPos-1][here->yPos+1][here->zPos]->block->NotY!=2)
				{
					return -3;
				}
				else if(here->block->Y!=1 && here->block->Y!=2 &&
					World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->NotY!=1 && World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->NotY!=2 &&
					World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->NotX!=1 && World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->NotX!=2 &&
					World::me->cube[here->xPos-1][here->yPos+1][here->zPos]->block->X!=1 && World::me->cube[here->xPos-1][here->yPos+1][here->zPos]->block->X!=2)
				{
					return -3;
				}
			}
			else if(xMove==-1 && yMove==-1)
			{
				if(here->block->NotX!=1 && here->block->NotX!=2 &&
					World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->X!=1 && World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->X!=2 &&
					World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->NotY!=1 && World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->NotY!=2 &&
					World::me->cube[here->xPos-1][here->yPos-1][here->zPos]->block->Y!=1 && World::me->cube[here->xPos-1][here->yPos-1][here->zPos]->block->Y!=2)
				{
					return -3;
				}
				else if(here->block->NotY!=1 && here->block->NotY!=2 &&
					World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->Y!=1 && World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->Y!=2 &&
					World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->NotX!=1 && World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->NotX!=2 &&
					World::me->cube[here->xPos-1][here->yPos-1][here->zPos]->block->X!=1 && World::me->cube[here->xPos-1][here->yPos-1][here->zPos]->block->X!=2)
				{
					return -3;
				}
			}
			else
			{
				std::cout << "How did we reach this failpart at z+ canWalk?";
				World::me->pause();
				return -666;
			}
		}
		else if(xMove==1)
		{
			if(here->block->X!=1 && here->block->X!=2 &&
				World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->NotX!=1 && World::me->cube[here->xPos+1][here->yPos][here->zPos]->block->NotX!=2)
			{
				return -3;
			}
		}
		else if(xMove==-1)
		{
			if(here->block->NotX!=1 && here->block->NotX!=2 &&
				World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->X!=1 && World::me->cube[here->xPos-1][here->yPos][here->zPos]->block->X!=2)
			{
				return -3;
			}
		}
		else if(yMove==1)
		{
			if(here->block->Y!=1 && here->block->Y!=2 &&
				World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->NotY!=1 && World::me->cube[here->xPos][here->yPos+1][here->zPos]->block->NotY!=2)
			{
				return -3;
			}
		}
		else if(yMove==-1)
		{
			if(here->block->NotY!=1 && here->block->NotY!=2 &&
				World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->Y!=1 && World::me->cube[here->xPos][here->yPos-1][here->zPos]->block->Y!=2)
			{
				return -3;
			}
		}
		else
		{
			std::cout << "How did we reach this SUPER failpart at z+ canWalk?";
			World::me->pause();
		}
	}

	if(there->block->center==3)
	{
		return there->block->id; //todo: do we also care if we're moving from inside a solid block? add in when phasing is in
	}

	if(there->block->species!="Empty")
	{
		std::cout << "We're trying to riskwalk into one of these, but we missed all the checks before rturning 0? " << there->block->name(2);
		World::me->pause();
		return -666;
	}

	// Walking onto map edge
	if(there->nogo)
	{
		std::cout << "We're trying to riskwalk onto a map edge, but we passed everything up to hitting this nogo check? " << there->block->name(2);
		World::me->pause();
		return -3;
	}

	return 0;

	/*
	if(there->nogo)
	{
		return there->center;
	}

	if(World::me->distance(here->xPos, here->yPos, here->zPos, there->xPos, there->yPos, there->zPos) >= 2)
	{
		std::cout << "Why is unit " << species << " trying to canWalk more than one square away?";
		World::me->pause();
		return new Block(-1, -1, -1);
	}

	if(!here->center->platform && !World::me->cube[here->xPos][here->yPos][here->zPos-1]->center->standable)
	{
		return new Block(-1, -1, -1); //TODO: do we care if we're starting on air?
	}

	if(!there->center->platform && !World::me->cube[there->xPos][there->yPos][there->zPos-1]->center->standable)
	{
		return new Block(-1, -1, -1); // Can't walk onto open air
	}

	if(here->zPos+1==there->zPos) // if there is +z
	{
		if(here->xPos==there->xPos && here->yPos==there->yPos) // directly +z
		{
			if(!here->center->stairs)
			{
				return new Block(-1, -1, -1); // Can't walk directly up without stairs
			}
		}
		else if(World::me->cube[here->xPos][here->yPos][here->zPos+1]->center->edgy)
		{
			return World::me->cube[here->xPos][here->yPos][here->zPos+1]->center; // Block above here is edgy = blocking
		}
		else if(World::me->cube[there->xPos][there->yPos][there->zPos-1]->center->edgy)
		{
			return World::me->cube[there->xPos][there->yPos][there->zPos-1]->center; // Block below there is edgy = blocking
		}
		else if(!World::me->cube[there->xPos][there->yPos][there->zPos-1]->center->ramp)
		{
			return new Block(-1, -1, -1); // Block below there isn't a ramp = can't climb up
		}
		else if(here->xPos!=there->xPos && here->yPos!=there->yPos)
		{
			int xMove=-1;
			if(here->xPos+1==there->xPos)
			{
				xMove=1;
			}

			int yMove=-1;
			if(here->yPos+1==there->yPos)
			{
				yMove=1;
			}

			if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center->edgy)
			{
				return World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center; // lower x side is edgy = blocking
			}

			if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center->edgy)
			{
				return World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center; // lower y side is edgy = blocking
			}

			if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos+1]->center->edgy)
			{
				return World::me->cube[here->xPos+xMove][here->yPos][here->zPos+1]->center; // upper x side is edgy = blocking
			}

			if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos+1]->center->edgy)
			{
				return World::me->cube[here->xPos][here->yPos+yMove][here->zPos+1]->center; // upper y side is edgy = blocking
			}
		}
	}
	else if(here->zPos-1==there->zPos) // if there is -z
	{
		if(here->xPos==there->xPos && here->yPos==there->yPos) // directly -z
		{
			if(!there->center->stairs)
			{
				return new Block(-1, -1, -1); // Can't walk directly down without stairs
			}
		}
		else if(World::me->cube[there->xPos][there->yPos][there->zPos+1]->center->edgy)
		{
			return World::me->cube[there->xPos][there->yPos][there->zPos+1]->center; // Block above there is edgy = blocking
		}
		else if(World::me->cube[here->xPos][here->yPos][here->zPos-1]->center->edgy)
		{
			return World::me->cube[here->xPos][here->yPos][here->zPos-1]->center; // Block below here is edgy = blocking
		}
		else if(World::me->cube[here->xPos][here->yPos][here->zPos-1]->center->ramp)
		{
			return new Block(-1, -1, -1); // Block below here isn't a ramp = can't climb back up
		}
		else if(here->xPos!=there->xPos && here->yPos!=there->yPos)
		{
			int xMove=-1;
			if(here->xPos+1==there->xPos)
			{
				xMove=1;
			}

			int yMove=-1;
			if(here->yPos+1==there->yPos)
			{
				yMove=1;
			}

			if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center->edgy)
			{
				return World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center; // upper x side is edgy = blocking
			}

			if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center->edgy)
			{
				return World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center; // upper y side is edgy = blocking
			}

			if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos-1]->center->edgy)
			{
				return World::me->cube[here->xPos+xMove][here->yPos][here->zPos-1]->center; // x side is edgy = blocking
			}

			if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos-1]->center->edgy)
			{
				return World::me->cube[here->xPos][here->yPos+yMove][here->zPos-1]->center; // y side is edgy = blocking
			}
		}
	}
	else if(here->xPos!=there->xPos && here->yPos!=there->yPos)
	{
		int xMove=-1;
		if(here->xPos+1==there->xPos)
		{
			xMove=1;
		} //TODO: can math this shorter somehow?

		int yMove=-1;
		if(here->yPos+1==there->yPos)
		{
			yMove=1;
		}

		if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center->edgy)
		{
			return World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center; // x side is edgy = blocking
		}

		if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center->edgy)
		{
			return World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center; // y side is edgy = blocking
		}
	}

	if(!there->center->passable)
	{
		return there->center;
	}

	return NULL;
*/

//	  #'s 	Sizes			is blocked by (at least)
//	 -------------------------------------------
//	   0   	ghosts  		sealed
//	   1   	flying / gas  	solid walls
//	   2   	tiny / items  	buildings
//	   3   	small  			huge / enemy small
//	   4   	medium  		medium / enemy small
//	   5   	huge 			small
//	   6  	building		tiny / items
//	   7   	solid wall		flying / gas
//	   8   	sealed	 		anything

	/*
	std::list<Unit*>::iterator thing;
	if(place->units.empty())
	{
		return true;
	}
	else if(place->sizeList[8]!=0)
	{
		return false;
	}
	else if(size==0 || tags.count(PHASING)!=0)
	{
		//TODO: is this true?
		return true;
	}
	else if(!visible || place->viewers.count(this)==0)
	{
		return place->sizeList[6]==0;
	}
	else if(size==1 || tags.count(FLYING)!=0)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if(((*thing)->size>=6 && (*thing)->tags.count(PHASING)==0 && (*thing)->visible))
			{
				return false;
			}
		}

		return true;
	}
	else if(size==2)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if(((*thing)->size>=5 && (*thing)->tags.count(PHASING)==0 && (*thing)->visible))
			{
				return false;
			}
		}

		return true;
	}
	else if(size==3)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->tags.count(PHASING)==0 && ((*thing)->size>=6 || ((*thing)->visible && ((*thing)->size>=5 || ((*thing)->size>=3 && (*thing)->team!=team)))))
			{
				return false;
			}
		}

		return true;
	}
	else if(size==4)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->tags.count(PHASING)==0 && ((*thing)->size>=6 || ((*thing)->visible && ((*thing)->size>=4 || ((*thing)->size>=3 && (*thing)->team!=team)))))
			{
				return false;
			}
		}

		return true;
	}
	else if(size==5)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->tags.count(PHASING)==0 && ((*thing)->size>=6 || ((*thing)->visible && (*thing)->size>=3)))
			{
				return false;
			}
		}

		return true;
	}

	return false;
	*/
}

int Unit::canFly(Square* here, Square* there) {
	// Returns: -2 = couldn't letMove, -1 = same square, 0 = canMove, 1+ = id of blocking entity

	if(here->xPos==there->xPos && here->yPos==there->yPos && here->zPos==there->zPos)
	{
		return -1;
	}

	// More than 1 square away
	if(World::me->distance(here->xPos, here->yPos, here->zPos, there->xPos, there->yPos, there->zPos) >= 2)
	{
		std::cout << "Why is unit " << name(2) << " trying to canfly more than one square away?";
		World::me->pause();
		return -666;
	}

	int minBlocking=0;

	int xMove=0;
	if(here->xPos > there->xPos)
	{
		xMove=-1;
		minBlocking++;
	}
	else if(here->xPos < there->xPos)
	{
		xMove=1;
		minBlocking++;
	}

	int yMove=0;
	if(here->yPos > there->yPos)
	{
		yMove=-1;
		minBlocking++;
	}
	else if(here->yPos < there->yPos)
	{
		yMove=1;
		minBlocking++;
	}

	int zMove=0;
	if(here->zPos > there->zPos)
	{
		zMove=-1;
		minBlocking++;
	}
	else if(here->zPos < there->zPos)
	{
		zMove=1;
		minBlocking++;
	}

	if(minBlocking==0)
	{
		std::cout << "Why is item " << name(2) << " failing hard at minBlocking?";
		World::me->pause();
		return -666;
	}
	else if(minBlocking==1)
	{
		minBlocking=2;
	}
	else
	{
		minBlocking=4;
	}

	for(int i=std::min(0, xMove); i<=std::max(0, xMove);i++)
	{
		for(int j=std::min(0, yMove); j<=std::max(0, yMove);j++)
		{
			for(int k=std::min(0, zMove); k<=std::max(0, zMove);k++)
			{
				if(xMove!=0)
				{
					if(i==std::min(0, xMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->X>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
					else if(i==std::max(0, xMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->NotX>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
				}

				if(yMove!=0)
				{
					if(j==std::min(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->Y>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
					else if(j==std::max(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->NotY>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
				}

				if(zMove!=0)
				{
					if(k==std::min(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->Z>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
					else if(k==std::max(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->NotZ>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
				}
			}
		}
	}

	if(there->block->center==3)
	{
		return there->block->id; //todo: do we also care if we're moving from inside a solid block? add in when phasing is in
	}

	if(there->block->species!="Empty")
	{
		std::cout << "We're trying to fly into one of these, but we missed all the checks before rturning 0? " << there->block->name(2);
		World::me->pause();
		return -666;
	}

	// Walking onto map edge
	if(there->nogo)
	{
		std::cout << "We're trying to riskwalk onto a map edge, but we passed everything up to hitting this nogo check? " << there->block->name(2);
		World::me->pause();
		return there->block->id;
	}

	return 0;

	/*
	if(there->nogo)
	{
		return there->center;
	}

	if(World::me->distance(here->xPos, here->yPos, here->zPos, there->xPos, there->yPos, there->zPos) >= 2)
	{
		std::cout << "Why is unit " << species << " trying to canWalk more than one square away?";
		World::me->pause();
		return new Block(-1, -1, -1);
	}

	if(!here->center->platform && !World::me->cube[here->xPos][here->yPos][here->zPos-1]->center->standable)
	{
		return new Block(-1, -1, -1); //TODO: do we care if we're starting on air?
	}

	if(!there->center->platform && !World::me->cube[there->xPos][there->yPos][there->zPos-1]->center->standable)
	{
		return new Block(-1, -1, -1); // Can't walk onto open air
	}

	if(here->zPos+1==there->zPos) // if there is +z
	{
		if(here->xPos==there->xPos && here->yPos==there->yPos) // directly +z
		{
			if(!here->center->stairs)
			{
				return new Block(-1, -1, -1); // Can't walk directly up without stairs
			}
		}
		else if(World::me->cube[here->xPos][here->yPos][here->zPos+1]->center->edgy)
		{
			return World::me->cube[here->xPos][here->yPos][here->zPos+1]->center; // Block above here is edgy = blocking
		}
		else if(World::me->cube[there->xPos][there->yPos][there->zPos-1]->center->edgy)
		{
			return World::me->cube[there->xPos][there->yPos][there->zPos-1]->center; // Block below there is edgy = blocking
		}
		else if(!World::me->cube[there->xPos][there->yPos][there->zPos-1]->center->ramp)
		{
			return new Block(-1, -1, -1); // Block below there isn't a ramp = can't climb up
		}
		else if(here->xPos!=there->xPos && here->yPos!=there->yPos)
		{
			int xMove=-1;
			if(here->xPos+1==there->xPos)
			{
				xMove=1;
			}

			int yMove=-1;
			if(here->yPos+1==there->yPos)
			{
				yMove=1;
			}

			if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center->edgy)
			{
				return World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center; // lower x side is edgy = blocking
			}

			if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center->edgy)
			{
				return World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center; // lower y side is edgy = blocking
			}

			if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos+1]->center->edgy)
			{
				return World::me->cube[here->xPos+xMove][here->yPos][here->zPos+1]->center; // upper x side is edgy = blocking
			}

			if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos+1]->center->edgy)
			{
				return World::me->cube[here->xPos][here->yPos+yMove][here->zPos+1]->center; // upper y side is edgy = blocking
			}
		}
	}
	else if(here->zPos-1==there->zPos) // if there is -z
	{
		if(here->xPos==there->xPos && here->yPos==there->yPos) // directly -z
		{
			if(!there->center->stairs)
			{
				return new Block(-1, -1, -1); // Can't walk directly down without stairs
			}
		}
		else if(World::me->cube[there->xPos][there->yPos][there->zPos+1]->center->edgy)
		{
			return World::me->cube[there->xPos][there->yPos][there->zPos+1]->center; // Block above there is edgy = blocking
		}
		else if(World::me->cube[here->xPos][here->yPos][here->zPos-1]->center->edgy)
		{
			return World::me->cube[here->xPos][here->yPos][here->zPos-1]->center; // Block below here is edgy = blocking
		}
		else if(World::me->cube[here->xPos][here->yPos][here->zPos-1]->center->ramp)
		{
			return new Block(-1, -1, -1); // Block below here isn't a ramp = can't climb back up
		}
		else if(here->xPos!=there->xPos && here->yPos!=there->yPos)
		{
			int xMove=-1;
			if(here->xPos+1==there->xPos)
			{
				xMove=1;
			}

			int yMove=-1;
			if(here->yPos+1==there->yPos)
			{
				yMove=1;
			}

			if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center->edgy)
			{
				return World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center; // upper x side is edgy = blocking
			}

			if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center->edgy)
			{
				return World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center; // upper y side is edgy = blocking
			}

			if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos-1]->center->edgy)
			{
				return World::me->cube[here->xPos+xMove][here->yPos][here->zPos-1]->center; // x side is edgy = blocking
			}

			if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos-1]->center->edgy)
			{
				return World::me->cube[here->xPos][here->yPos+yMove][here->zPos-1]->center; // y side is edgy = blocking
			}
		}
	}
	else if(here->xPos!=there->xPos && here->yPos!=there->yPos)
	{
		int xMove=-1;
		if(here->xPos+1==there->xPos)
		{
			xMove=1;
		} //TODO: can math this shorter somehow?

		int yMove=-1;
		if(here->yPos+1==there->yPos)
		{
			yMove=1;
		}

		if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center->edgy)
		{
			return World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center; // x side is edgy = blocking
		}

		if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center->edgy)
		{
			return World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center; // y side is edgy = blocking
		}
	}

	if(!there->center->passable)
	{
		return there->center;
	}

	return NULL;
*/

//	  #'s 	Sizes			is blocked by (at least)
//	 -------------------------------------------
//	   0   	ghosts  		sealed
//	   1   	flying / gas  	solid walls
//	   2   	tiny / items  	buildings
//	   3   	small  			huge / enemy small
//	   4   	medium  		medium / enemy small
//	   5   	huge 			small
//	   6  	building		tiny / items
//	   7   	solid wall		flying / gas
//	   8   	sealed	 		anything

	/*
	std::list<Unit*>::iterator thing;
	if(place->units.empty())
	{
		return true;
	}
	else if(place->sizeList[8]!=0)
	{
		return false;
	}
	else if(size==0 || tags.count(PHASING)!=0)
	{
		//TODO: is this true?
		return true;
	}
	else if(!visible || place->viewers.count(this)==0)
	{
		return place->sizeList[6]==0;
	}
	else if(size==1 || tags.count(FLYING)!=0)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if(((*thing)->size>=6 && (*thing)->tags.count(PHASING)==0 && (*thing)->visible))
			{
				return false;
			}
		}

		return true;
	}
	else if(size==2)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if(((*thing)->size>=5 && (*thing)->tags.count(PHASING)==0 && (*thing)->visible))
			{
				return false;
			}
		}

		return true;
	}
	else if(size==3)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->tags.count(PHASING)==0 && ((*thing)->size>=6 || ((*thing)->visible && ((*thing)->size>=5 || ((*thing)->size>=3 && (*thing)->team!=team)))))
			{
				return false;
			}
		}

		return true;
	}
	else if(size==4)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->tags.count(PHASING)==0 && ((*thing)->size>=6 || ((*thing)->visible && ((*thing)->size>=4 || ((*thing)->size>=3 && (*thing)->team!=team)))))
			{
				return false;
			}
		}

		return true;
	}
	else if(size==5)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->tags.count(PHASING)==0 && ((*thing)->size>=6 || ((*thing)->visible && (*thing)->size>=3)))
			{
				return false;
			}
		}

		return true;
	}

	return false;
	*/
}

int Unit::canMove(Square* here, Square* there) {
	return canMove(here, there, NULL);
}

int Unit::canMove(Square* here, Square* there, Unit* ignore) {
	// Returns: -2 = couldn't letMove, -1 = same square, 0 = canMove, 1+ = id of blocking entity

	if(here->xPos==there->xPos && here->yPos==there->yPos && here->zPos==there->zPos)
	{
		return -1;
	}

	// More than 1 square away
	if(World::me->distance(here->xPos, here->yPos, here->zPos, there->xPos, there->yPos, there->zPos) >= 2)
	{
		std::cout << "Why is unit " << name(2) << " trying to canMove more than one square away?";
		World::me->pause();
		return -666;
	}

	int minBlocking=0;

	int xMove=0;
	if(here->xPos > there->xPos)
	{
		xMove=-1;
		minBlocking++;
	}
	else if(here->xPos < there->xPos)
	{
		xMove=1;
		minBlocking++;
	}

	int yMove=0;
	if(here->yPos > there->yPos)
	{
		yMove=-1;
		minBlocking++;
	}
	else if(here->yPos < there->yPos)
	{
		yMove=1;
		minBlocking++;
	}

	int zMove=0;
	if(here->zPos > there->zPos)
	{
		zMove=-1;
		minBlocking++;
	}
	else if(here->zPos < there->zPos)
	{
		zMove=1;
		minBlocking++;
	}

	if(minBlocking==0)
	{
		std::cout << "Why is item " << name(2) << " failing hard at canMove minBlocking?";
		World::me->pause();
		return -666;
	}
	else if(minBlocking==1)
	{
		minBlocking=2;
	}
	else
	{
		minBlocking=4;
	}

	double bestDist=999;
	int bestId=-666;

	for(int i=std::min(0, xMove); i<=std::max(0, xMove);i++)
	{
		for(int j=std::min(0, yMove); j<=std::max(0, yMove);j++)
		{
			for(int k=std::min(0, zMove); k<=std::max(0, zMove);k++)
			{
				bool hit=false;

				if(xMove!=0)
				{
					if(i==std::min(0, xMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->X>=minBlocking)
					{
						hit=true;
					}
					else if(i==std::max(0, xMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->NotX>=minBlocking)
					{
						hit=true;
					}
				}

				if(yMove!=0 && !hit)
				{
					if(j==std::min(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->Y>=minBlocking)
					{
						hit=true;
					}
					else if(j==std::max(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->NotY>=minBlocking)
					{
						hit=true;
					}
				}

				if(zMove!=0 && !hit)
				{
					if(k==std::min(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->Z>=minBlocking)
					{
						hit=true;
					}
					else if(k==std::max(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->NotZ>=minBlocking)
					{
						hit=true;
					}
				}

				if(hit && World::me->distance(here->xPos, here->yPos, here->zPos, here->xPos+i, here->yPos+j, here->zPos+k)<bestDist)
				{
					bestDist=World::me->distance(here->xPos, here->yPos, here->zPos, here->xPos+i, here->yPos+j, here->zPos+k);
					bestId=World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
				}
			}
		}
	}

	if(bestId!=-666)
	{
		return bestId;
	}

	if(there->block->center==3)
	{
		return there->block->id; //todo: do we also care if we're moving from inside a solid block? add in when phasing is in
	}

	if(there->block->species!="Empty")
	{
		std::cout << "We're trying to canMove into one of these, but we missed all the checks before rturning 0? " << there->block->name(2);
		World::me->pause();
		return -666;
	}

	// Walking onto map edge
	if(there->nogo)
	{
		std::cout << "We're trying to canMove into a nogo zone, but we didn't hit anything up to this final nogo check? " << there->block->name(2);
		World::me->pause();
		return there->block->id;
	}

	// TODO: search through all units for anyone that could block you, except ignore the ignore unit above

	return 0;

	/*
	if(there->nogo)
	{
		return there->center;
	}

	if(World::me->distance(here->xPos, here->yPos, here->zPos, there->xPos, there->yPos, there->zPos) >= 2)
	{
		std::cout << "Why is unit " << species << " trying to canWalk more than one square away?";
		World::me->pause();
		return new Block(-1, -1, -1);
	}

	if(!here->center->platform && !World::me->cube[here->xPos][here->yPos][here->zPos-1]->center->standable)
	{
		return new Block(-1, -1, -1); //TODO: do we care if we're starting on air?
	}

	if(!there->center->platform && !World::me->cube[there->xPos][there->yPos][there->zPos-1]->center->standable)
	{
		return new Block(-1, -1, -1); // Can't walk onto open air
	}

	if(here->zPos+1==there->zPos) // if there is +z
	{
		if(here->xPos==there->xPos && here->yPos==there->yPos) // directly +z
		{
			if(!here->center->stairs)
			{
				return new Block(-1, -1, -1); // Can't walk directly up without stairs
			}
		}
		else if(World::me->cube[here->xPos][here->yPos][here->zPos+1]->center->edgy)
		{
			return World::me->cube[here->xPos][here->yPos][here->zPos+1]->center; // Block above here is edgy = blocking
		}
		else if(World::me->cube[there->xPos][there->yPos][there->zPos-1]->center->edgy)
		{
			return World::me->cube[there->xPos][there->yPos][there->zPos-1]->center; // Block below there is edgy = blocking
		}
		else if(!World::me->cube[there->xPos][there->yPos][there->zPos-1]->center->ramp)
		{
			return new Block(-1, -1, -1); // Block below there isn't a ramp = can't climb up
		}
		else if(here->xPos!=there->xPos && here->yPos!=there->yPos)
		{
			int xMove=-1;
			if(here->xPos+1==there->xPos)
			{
				xMove=1;
			}

			int yMove=-1;
			if(here->yPos+1==there->yPos)
			{
				yMove=1;
			}

			if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center->edgy)
			{
				return World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center; // lower x side is edgy = blocking
			}

			if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center->edgy)
			{
				return World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center; // lower y side is edgy = blocking
			}

			if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos+1]->center->edgy)
			{
				return World::me->cube[here->xPos+xMove][here->yPos][here->zPos+1]->center; // upper x side is edgy = blocking
			}

			if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos+1]->center->edgy)
			{
				return World::me->cube[here->xPos][here->yPos+yMove][here->zPos+1]->center; // upper y side is edgy = blocking
			}
		}
	}
	else if(here->zPos-1==there->zPos) // if there is -z
	{
		if(here->xPos==there->xPos && here->yPos==there->yPos) // directly -z
		{
			if(!there->center->stairs)
			{
				return new Block(-1, -1, -1); // Can't walk directly down without stairs
			}
		}
		else if(World::me->cube[there->xPos][there->yPos][there->zPos+1]->center->edgy)
		{
			return World::me->cube[there->xPos][there->yPos][there->zPos+1]->center; // Block above there is edgy = blocking
		}
		else if(World::me->cube[here->xPos][here->yPos][here->zPos-1]->center->edgy)
		{
			return World::me->cube[here->xPos][here->yPos][here->zPos-1]->center; // Block below here is edgy = blocking
		}
		else if(World::me->cube[here->xPos][here->yPos][here->zPos-1]->center->ramp)
		{
			return new Block(-1, -1, -1); // Block below here isn't a ramp = can't climb back up
		}
		else if(here->xPos!=there->xPos && here->yPos!=there->yPos)
		{
			int xMove=-1;
			if(here->xPos+1==there->xPos)
			{
				xMove=1;
			}

			int yMove=-1;
			if(here->yPos+1==there->yPos)
			{
				yMove=1;
			}

			if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center->edgy)
			{
				return World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center; // upper x side is edgy = blocking
			}

			if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center->edgy)
			{
				return World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center; // upper y side is edgy = blocking
			}

			if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos-1]->center->edgy)
			{
				return World::me->cube[here->xPos+xMove][here->yPos][here->zPos-1]->center; // x side is edgy = blocking
			}

			if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos-1]->center->edgy)
			{
				return World::me->cube[here->xPos][here->yPos+yMove][here->zPos-1]->center; // y side is edgy = blocking
			}
		}
	}
	else if(here->xPos!=there->xPos && here->yPos!=there->yPos)
	{
		int xMove=-1;
		if(here->xPos+1==there->xPos)
		{
			xMove=1;
		} //TODO: can math this shorter somehow?

		int yMove=-1;
		if(here->yPos+1==there->yPos)
		{
			yMove=1;
		}

		if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center->edgy)
		{
			return World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center; // x side is edgy = blocking
		}

		if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center->edgy)
		{
			return World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center; // y side is edgy = blocking
		}
	}

	if(!there->center->passable)
	{
		return there->center;
	}

	return NULL;
*/

//	  #'s 	Sizes			is blocked by (at least)
//	 -------------------------------------------
//	   0   	ghosts  		sealed
//	   1   	flying / gas  	solid walls
//	   2   	tiny / items  	buildings
//	   3   	small  			huge / enemy small
//	   4   	medium  		medium / enemy small
//	   5   	huge 			small
//	   6  	building		tiny / items
//	   7   	solid wall		flying / gas
//	   8   	sealed	 		anything

	/*
	std::list<Unit*>::iterator thing;
	if(place->units.empty())
	{
		return true;
	}
	else if(place->sizeList[8]!=0)
	{
		return false;
	}
	else if(size==0 || tags.count(PHASING)!=0)
	{
		//TODO: is this true?
		return true;
	}
	else if(!visible || place->viewers.count(this)==0)
	{
		return place->sizeList[6]==0;
	}
	else if(size==1 || tags.count(FLYING)!=0)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if(((*thing)->size>=6 && (*thing)->tags.count(PHASING)==0 && (*thing)->visible))
			{
				return false;
			}
		}

		return true;
	}
	else if(size==2)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if(((*thing)->size>=5 && (*thing)->tags.count(PHASING)==0 && (*thing)->visible))
			{
				return false;
			}
		}

		return true;
	}
	else if(size==3)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->tags.count(PHASING)==0 && ((*thing)->size>=6 || ((*thing)->visible && ((*thing)->size>=5 || ((*thing)->size>=3 && (*thing)->team!=team)))))
			{
				return false;
			}
		}

		return true;
	}
	else if(size==4)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->tags.count(PHASING)==0 && ((*thing)->size>=6 || ((*thing)->visible && ((*thing)->size>=4 || ((*thing)->size>=3 && (*thing)->team!=team)))))
			{
				return false;
			}
		}

		return true;
	}
	else if(size==5)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->tags.count(PHASING)==0 && ((*thing)->size>=6 || ((*thing)->visible && (*thing)->size>=3)))
			{
				return false;
			}
		}

		return true;
	}

	return false;
	*/
}


int Unit::canPlanMove(Square* here, Square* there) {
	return canPlanMove(here, there, NULL);
}

int Unit::canPlanMove(Square* here, Square* there, Unit* ignore) {
	// Returns: -3 = out of bounds target, -2 = couldn't letMove, -1 = same square, 0 = canMove, 1+ = id of blocking entity


	if(there->nogo)
	{
		return -3; // Walking onto map edge
	}

	if(here->xPos==there->xPos && here->yPos==there->yPos && here->zPos==there->zPos)
	{
		return -1;
	}

	// More than 1 square away
	if(World::me->distance(here->xPos, here->yPos, here->zPos, there->xPos, there->yPos, there->zPos) >= 2)
	{
		std::cout << "Why is unit " << name(2) << " trying to canfly more than one square away?";
		World::me->pause();
		return -666;
	}

	int minBlocking=0;

	int xMove=0;
	if(here->xPos > there->xPos)
	{
		xMove=-1;
		minBlocking++;
	}
	else if(here->xPos < there->xPos)
	{
		xMove=1;
		minBlocking++;
	}

	int yMove=0;
	if(here->yPos > there->yPos)
	{
		yMove=-1;
		minBlocking++;
	}
	else if(here->yPos < there->yPos)
	{
		yMove=1;
		minBlocking++;
	}

	int zMove=0;
	if(here->zPos > there->zPos)
	{
		zMove=-1;
		minBlocking++;
	}
	else if(here->zPos < there->zPos)
	{
		zMove=1;
		minBlocking++;
	}

	if(minBlocking==0)
	{
		std::cout << "Why is item " << name(2) << " failing hard at minBlocking?";
		World::me->pause();
		return -666;
	}
	else if(minBlocking==1)
	{
		minBlocking=2;
	}
	else
	{
		minBlocking=4;
	}

	for(int i=std::min(0, xMove); i<=std::max(0, xMove);i++)
	{
		for(int j=std::min(0, yMove); j<=std::max(0, yMove);j++)
		{
			for(int k=std::min(0, zMove); k<=std::max(0, zMove);k++)
			{
				if(xMove!=0)
				{
					if(i==std::min(0, xMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->X>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
					else if(i==std::max(0, xMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->NotX>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
				}

				if(yMove!=0)
				{
					if(j==std::min(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->Y>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
					else if(j==std::max(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->NotY>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
				}

				if(zMove!=0)
				{
					if(k==std::min(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->Z>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
					else if(k==std::max(0, yMove) && World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->NotZ>=minBlocking)
					{
						return World::me->cube[here->xPos+i][here->yPos+j][here->zPos+k]->block->id;
					}
				}
			}
		}
	}

	if(there->block->center==3)
	{
		return there->block->id; //todo: do we also care if we're moving from inside a solid block? add in when phasing is in
	}

	if(there->block->species!="Empty")
	{
		std::cout << "We're trying to fly into one of these, but we missed all the checks before rturning 0? " << there->block->name(2);
		World::me->pause();
		return -666;
	}

	return 0;

	/*
	if(there->nogo)
	{
		return there->center;
	}

	if(World::me->distance(here->xPos, here->yPos, here->zPos, there->xPos, there->yPos, there->zPos) >= 2)
	{
		std::cout << "Why is unit " << species << " trying to canWalk more than one square away?";
		World::me->pause();
		return new Block(-1, -1, -1);
	}

	if(!here->center->platform && !World::me->cube[here->xPos][here->yPos][here->zPos-1]->center->standable)
	{
		return new Block(-1, -1, -1); //TODO: do we care if we're starting on air?
	}

	if(!there->center->platform && !World::me->cube[there->xPos][there->yPos][there->zPos-1]->center->standable)
	{
		return new Block(-1, -1, -1); // Can't walk onto open air
	}

	if(here->zPos+1==there->zPos) // if there is +z
	{
		if(here->xPos==there->xPos && here->yPos==there->yPos) // directly +z
		{
			if(!here->center->stairs)
			{
				return new Block(-1, -1, -1); // Can't walk directly up without stairs
			}
		}
		else if(World::me->cube[here->xPos][here->yPos][here->zPos+1]->center->edgy)
		{
			return World::me->cube[here->xPos][here->yPos][here->zPos+1]->center; // Block above here is edgy = blocking
		}
		else if(World::me->cube[there->xPos][there->yPos][there->zPos-1]->center->edgy)
		{
			return World::me->cube[there->xPos][there->yPos][there->zPos-1]->center; // Block below there is edgy = blocking
		}
		else if(!World::me->cube[there->xPos][there->yPos][there->zPos-1]->center->ramp)
		{
			return new Block(-1, -1, -1); // Block below there isn't a ramp = can't climb up
		}
		else if(here->xPos!=there->xPos && here->yPos!=there->yPos)
		{
			int xMove=-1;
			if(here->xPos+1==there->xPos)
			{
				xMove=1;
			}

			int yMove=-1;
			if(here->yPos+1==there->yPos)
			{
				yMove=1;
			}

			if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center->edgy)
			{
				return World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center; // lower x side is edgy = blocking
			}

			if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center->edgy)
			{
				return World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center; // lower y side is edgy = blocking
			}

			if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos+1]->center->edgy)
			{
				return World::me->cube[here->xPos+xMove][here->yPos][here->zPos+1]->center; // upper x side is edgy = blocking
			}

			if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos+1]->center->edgy)
			{
				return World::me->cube[here->xPos][here->yPos+yMove][here->zPos+1]->center; // upper y side is edgy = blocking
			}
		}
	}
	else if(here->zPos-1==there->zPos) // if there is -z
	{
		if(here->xPos==there->xPos && here->yPos==there->yPos) // directly -z
		{
			if(!there->center->stairs)
			{
				return new Block(-1, -1, -1); // Can't walk directly down without stairs
			}
		}
		else if(World::me->cube[there->xPos][there->yPos][there->zPos+1]->center->edgy)
		{
			return World::me->cube[there->xPos][there->yPos][there->zPos+1]->center; // Block above there is edgy = blocking
		}
		else if(World::me->cube[here->xPos][here->yPos][here->zPos-1]->center->edgy)
		{
			return World::me->cube[here->xPos][here->yPos][here->zPos-1]->center; // Block below here is edgy = blocking
		}
		else if(World::me->cube[here->xPos][here->yPos][here->zPos-1]->center->ramp)
		{
			return new Block(-1, -1, -1); // Block below here isn't a ramp = can't climb back up
		}
		else if(here->xPos!=there->xPos && here->yPos!=there->yPos)
		{
			int xMove=-1;
			if(here->xPos+1==there->xPos)
			{
				xMove=1;
			}

			int yMove=-1;
			if(here->yPos+1==there->yPos)
			{
				yMove=1;
			}

			if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center->edgy)
			{
				return World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center; // upper x side is edgy = blocking
			}

			if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center->edgy)
			{
				return World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center; // upper y side is edgy = blocking
			}

			if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos-1]->center->edgy)
			{
				return World::me->cube[here->xPos+xMove][here->yPos][here->zPos-1]->center; // x side is edgy = blocking
			}

			if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos-1]->center->edgy)
			{
				return World::me->cube[here->xPos][here->yPos+yMove][here->zPos-1]->center; // y side is edgy = blocking
			}
		}
	}
	else if(here->xPos!=there->xPos && here->yPos!=there->yPos)
	{
		int xMove=-1;
		if(here->xPos+1==there->xPos)
		{
			xMove=1;
		} //TODO: can math this shorter somehow?

		int yMove=-1;
		if(here->yPos+1==there->yPos)
		{
			yMove=1;
		}

		if(World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center->edgy)
		{
			return World::me->cube[here->xPos+xMove][here->yPos][here->zPos]->center; // x side is edgy = blocking
		}

		if(World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center->edgy)
		{
			return World::me->cube[here->xPos][here->yPos+yMove][here->zPos]->center; // y side is edgy = blocking
		}
	}

	if(!there->center->passable)
	{
		return there->center;
	}

	return NULL;
*/

//	  #'s 	Sizes			is blocked by (at least)
//	 -------------------------------------------
//	   0   	ghosts  		sealed
//	   1   	flying / gas  	solid walls
//	   2   	tiny / items  	buildings
//	   3   	small  			huge / enemy small
//	   4   	medium  		medium / enemy small
//	   5   	huge 			small
//	   6  	building		tiny / items
//	   7   	solid wall		flying / gas
//	   8   	sealed	 		anything

	/*
	std::list<Unit*>::iterator thing;
	if(place->units.empty())
	{
		return true;
	}
	else if(place->sizeList[8]!=0)
	{
		return false;
	}
	else if(size==0 || tags.count(PHASING)!=0)
	{
		//TODO: is this true?
		return true;
	}
	else if(!visible || place->viewers.count(this)==0)
	{
		return place->sizeList[6]==0;
	}
	else if(size==1 || tags.count(FLYING)!=0)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if(((*thing)->size>=6 && (*thing)->tags.count(PHASING)==0 && (*thing)->visible))
			{
				return false;
			}
		}

		return true;
	}
	else if(size==2)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if(((*thing)->size>=5 && (*thing)->tags.count(PHASING)==0 && (*thing)->visible))
			{
				return false;
			}
		}

		return true;
	}
	else if(size==3)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->tags.count(PHASING)==0 && ((*thing)->size>=6 || ((*thing)->visible && ((*thing)->size>=5 || ((*thing)->size>=3 && (*thing)->team!=team)))))
			{
				return false;
			}
		}

		return true;
	}
	else if(size==4)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->tags.count(PHASING)==0 && ((*thing)->size>=6 || ((*thing)->visible && ((*thing)->size>=4 || ((*thing)->size>=3 && (*thing)->team!=team)))))
			{
				return false;
			}
		}

		return true;
	}
	else if(size==5)
	{
		for(thing=place->units.begin(); thing!=place->units.end(); thing++)
		{
			if((*thing)->tags.count(PHASING)==0 && ((*thing)->size>=6 || ((*thing)->visible && (*thing)->size>=3)))
			{
				return false;
			}
		}

		return true;
	}

	return false;
	*/
}

bool Unit::tryPath(int x, int y, int z, bool risky, int howClose) {
	// This is when you first want to tell a unit to path towards somewhere and leave the specifics to him
	// Returns: -3 = No movement actions, -2 = No possible path, -1 = Failed to move, 0 = Targeted same square so no movement, 1 = Moved, 2 = tried to move but hit something unexpected while attempting

	if(xPos==x && yPos==y && zPos==z)
	{
		return false;
	}

	std::vector<Actool*> possibleMoves=getActools("", MOVEMENT, NULL_ACTION_SUBTAG, 2);

	for(unsigned int i=0;i<possibleMoves.size();i++)
	{
			Square* nextMove=World::me->starPath(this, x, y, z, possibleMoves, risky, howClose);

			if(nextMove==NULL)
			{
				std::cout << "Why is tryMove returning null when it should have earlier?";
				World::me->pause();
				return false;
			}
			else if(nextMove->xPos>0)
			{
				return possibleMoves[i]->startAttempt(NULL, NULL, nextMove);
			}
	}

	return false;
}

int Unit::tryMove(int x, int y, int z, Entity* target) {
	// Returns: -3 = Can't canAttempt or out of bounds, -2 = couldn't letMove, -1 = already at target square, 0 = moved, 1+ = id of blocking entity
	// Unit's default trymove is just attempting an actionless trymove

	return tryMove(x, y, z, target, false, NULL, NULL);
}

int Unit::tryMove(int x, int y, int z, Entity* target, bool actionMove, Actool* moveActool, Unit* exception) {
	// actionMove: if true, use one of our actions to move manually, while false means we're being pushed by outside forces and need no action to move (aka legless man falling from gravity)
	// This doesn't handle energy adjustments, the action's attempt should
	// grappleException: if a unit is dragging me as they move and this is the move check for that, we're allowed to move if they're the only one holding us
	// Returns: -4 = no movement actions, -3 = Can't canAttempt or out of bounds, -2 = couldn't letMove, -1 = already at target square, 0 = moved, 1+ = id of blocking entity


	if(x<0 || x>=World::me->xMax || y<0 || y>=World::me->yMax || z<0 || z>=World::me->zMax)
	{
		return -3; // Out of bounds = fail
	}

	if(xPos==x && yPos==y && zPos==z)
	{
		return -1; // Same square = fail
	}

	if(actionMove) // If we're moving normally, work with our movement actions
	{
		if(moveActool==NULL)
		{
			Actool* movement=getActool("", MOVEMENT, NULL_ACTION_SUBTAG, NULL, NULL, World::me->cube[x][y][z]);

			if(movement==NULL)
			{
				return -4;
			}

			// Yes, do act->attempt below instead of another call to this same tryMove because it handles energy, but also make sure to correct the returns it gives
			int result=movement->tryAttempt(this, NULL, NULL, World::me->cube[x][y][z]);
			if(result<0)
			{
				std::cout << "??? " << name(2) << " said we can use this actool, but come time to do it returned less than 0? " << moveActool->act->actionName;
				World::me->pause();
				return -666;
			}
			return result;
		}

		if(moveActool->act->actionType==NULL_ACTION_TAG) //TODO: incorrect, check for all movement types?
		{
			std::cout << "??? " << name(2) << " trying to close move, but its using a non-move action? " << moveActool->act->actionName;
			World::me->pause();
			return -666;
		}

		if(!moveActool->canAttempt(NULL, NULL, World::me->cube[x][y][z]))
		{
			return -3;
		}
	}

	if(!letMove(x, y, z, exception)) // Just a check for if we're being held by someone else = can't move
	{
		return -2;
	}

	int hitResult=canMove(World::me->cube[xPos][yPos][zPos], World::me->cube[x][y][z], exception);

	if(hitResult>=0 && target!=NULL && target->xPos==x && target->yPos==y && target->zPos==z)
	{
		hitResult=target->id;
	}

	if(hitResult!=0)
	{
		if(hitResult<=0)
		{
			std::cout << "A " << name(2) << " is trying to tryMove, but went up to checking canMove and got " << hitResult << " instead of an id?" ;
			World::me->pause();
			return -666;
		}

		collide(World::me->getEntId(hitResult), true);
		return hitResult;
	}

	if(!canDragMove(this, true))
	{
		return -2;
	}

	World::me->moveUnit(this, x, y, z);
	return 0;
}

bool Unit::letMove(int x, int y, int z, Unit* exception) {
	// xyz can be -1 to see if the unit can move at all, or positive if they can move to a certain square
	// grappleException: if a unit is dragging me as they move and this is the move check for that, we're allowed to move if they're the only one holding us


	// TODO: when size / strength is put in, change all this

	std::vector<Item*> holdersBlob=getBlob(true, 0, -2, 0, this, -3, 0); // TODO: for now, only holders block movement. being embedded = you drag them along always

	for(unsigned int i=0;i<holdersBlob.size();i++)
	{
		if(holdersBlob[i]->owner!=this && holdersBlob[i]->owner!=exception)
		{
			return false;
		}
	}

	if(!canDragMove(exception, false)) // If we'd be prevented from moving due to someone embedded into us / holding us
	{
		return false; // if we're holding something someone else is holding, we CAN move, even if the item will be lost
	}

	// TODO: stati that forbid movement in a direction / a distance away from some centerpoint / being rooted

	return true;
}

bool Unit::canDragMove(Unit* exception, bool attempting) {
	// Are we allowed to move, or are people holding us / embedded into us that are too strong to move, meaning we can't move ourselves?
	// If attempting, we try and drag them all to the square we're in, or drop them if we can't drag them with us
	// If not attempting, we don't check if things we're holding can be dragged, we just assume we'll drop em when it happens

	std::vector<Unit*> movers;
	std::set<Unit*> checked;

	std::vector<Item*> checkingBlob=getBlob(false, 0, 0, 3, this, -3, 0); // Embedded check, where if we can't drag them with us we have to quit early

	for(unsigned int i=0;i<checkingBlob.size();i++)
	{
		if(checkingBlob[i]->owner==exception)
		{
			continue;  // We're being dragged by our siamese twin grappler, so if its them we can skip it
		}

		// TODO: if they're being held, and we can't shake off their holders, we stop

		// TODO: if they're bigger / heavier / what??? than us, we can't drag them
		return false;

		// TODO: then, if they can't canMove / letMove to our square, give up early here since we can't easily remove them

		// TODO: otherwise, add them to the mover / checked list so they follow us
	}



					// TODO: maybe combine these two? just add -2 to holdingLevel above and manually check there for if


	checkingBlob=getBlob(false, 0, -2, 3, this, -3, 0); // Being held check, where if we're being held at all we shake them off or get stopped early

	for(unsigned int i=0;i<checkingBlob.size();i++)
	{
		if(checkingBlob[i]->owner==exception || checked.count(checkingBlob[i]->owner)!=0)
		{
			continue;  // We're being pulled by our grappler, so if its them we can skip it
		}

		// TODO: we're embedded into someone who has an arrow embedded into them, and an enemy is holding the arrow: is that caught here?

		// TODO: if they're bigger / heavier / what??? than us, we can't shake them off
		return false;

		// TODO: and if they're holding us, make them drop us
	}



	if(!attempting) // If we're only testing to see if we COULD drag everyone else behind us, stop here. If problems arise in things we're holding, we could just drop em
	{
		return true;
	}

	 // Holding other units / items check, where if we can't bring it with us we can just drop it
	std::set<Unit*> droppables;
	checkingBlob=getBlob(false, 0, -1, 0, this, -1, 0); // All non-self-organ things we're holding, even if they have no owner

	for(unsigned int i=0;i<checkingBlob.size();i++)
	{
		if(checkingBlob[i]->owner!=NULL)
		{
			if(checked.count(checkingBlob[i]->owner)!=0)
			{
				continue; // We've already either agreed to move him if they were embedded before, or have already done the check below with another hand and dropped it already / added to movers
			}

			checked.insert(checkingBlob[i]->owner);
		}

		std::vector<Item*> holdersBlob=checkingBlob[i]->getBlob(-1, 0, -2, 3, this, -3, 0); // Any non-us holders of this object / its embedded blob

		bool contested=false;
		for(unsigned int j=0;j<holdersBlob.size();j++)
		{
			if(holdersBlob[j]->owner!=this) // If they're held by someone else, its contested = we drop it
			{
				contested=true; // TODO: instead, we should determine which of us is stronger and have the weaker guy drop it
				break;
			}
		}

		if(contested)
		{
			std::cout << name(0) << " is contested holding " << checkingBlob[i] << ", so I'm dropping it ";
			drop(checkingBlob[i], false);
		}
		else if(checkingBlob[i]->owner!=NULL &&
				(!checkingBlob[i]->owner->letMove(xPos, yPos, zPos, this) ||
				checkingBlob[i]->owner->canPlanMove(World::me->cube[checkingBlob[i]->owner->xPos][checkingBlob[i]->owner->yPos][checkingBlob[i]->owner->zPos], World::me->cube[xPos][yPos][zPos], this)!=0))
		{
			std::cout << name(0) << " is holding " << checkingBlob[i] << " but they can't follow my move, so I'm dropping it ";
			drop(checkingBlob[i], false);
		}
		else if(checkingBlob[i]->owner!=NULL)
		{
			// TODO: if they're bigger / heavier / what??? than us, we can't drag them
			movers.push_back(checkingBlob[i]->owner);
			droppables.insert(checkingBlob[i]->owner);
		}
		else
		{
			// If we're holding something that isn't an organ, at this point it can only be a held / subheld item AKA a sword, and it will be brought with us automatically no hassle

			// TODO: even if they're not an organ, should we care about their weight? carrying a giant's coprse = slow movement? or couldn't even grab it in the first place?
		}
	}

	// Now that we know all the people we're trying to move with us, we move them into our square first before moving ourselves
	for(unsigned int i=0;i<movers.size();i++)
	{
		// TODO: instead of always our square, imagine dragging 3 units behind us in 3 squares down a 3-wide hallway: they all just go straight down

		if(movers[i]->tryMove(xPos, yPos, zPos, NULL, false, NULL, this)!=0)
		{
			if(droppables.count(movers[i])!=0)
			{
				movers[i]->dropped(this, false); // If one of our held-only units is now blocked, we can just drop them
			}
			else
			{
				World::me->handleRefresh();
				return false; // TODO: 2 blocking units can move into the same square if they're dragged?
			}
		}
	}

	World::me->handleRefresh();
	return true;
}

void Unit::moved(int x, int y, int z, int oldX, int oldY, int oldZ) {
//	std::list<Status*> afflictions=stati;
//	for(std::list<Status*>::iterator affliction=afflictions.begin(); !afflictions.empty() && affliction!=afflictions.end(); affliction++)
//	{
//		(*affliction)->move();
//	}


	if(myGrav==NULL && fallCheck() && initStatus!=2)
	{
		std::cout << "(" << name(2) << " started to unitfall!) ";
		World::me->addGravity(new Gravity(this));
	}
}


void Unit::damage(int impactHit, int slashHit, int stabHit, int brokeHit, int maxHit, int soulHit, Entity* cause, Entity* source, bool canEmbed) {
	return damage(impactHit, slashHit, stabHit, brokeHit, maxHit, soulHit, cause, source, canEmbed, NULL);
}

void Unit::damage(int impactHit, int slashHit, int stabHit, int brokeHit, int maxHit, int soulHit, Entity* cause, Entity* source, bool canEmbed, Item* target) {

//	std::list<Status*> afflictions=stati;
//	for(std::list<Status*>::iterator affliction=afflictions.begin(); !afflictions.empty() && affliction!=afflictions.end(); affliction++)
//	{
//		amount=(*affliction)->damage(amount, distance, method, attacker);
//	}

	if(target!=NULL)
	{
		if(target->owner!=this)
		{
			std::cout << "??? " << name(2) << " was targeted on " << target->name(2) << ", but he doesn't have that part?";
			World::me->pause();
		}

		if(target->armor!=NULL)
		{
			std::cout << "??? " << name(2) << " was targeted on " << target->name(2) << ", but that part is armored?";
			World::me->pause();
		}


		target->damage(brokeHit, impactHit, slashHit, stabHit, maxHit, soulHit, cause, source, canEmbed);
		return;
	}
	else if(!parts.empty())
	{
		std::vector<Item*> attackables=(*parts.begin())->attackableBlob();

		if(attackables.empty())
		{
			std::cout << "Some dumbass unit doesn't have any attackable parts? " << name(2);
			World::me->pause();
			return;
		}

		int hit=World::me->random(1, attackables.size());

		for(int i=0;i<500;i++)
		{
			hit--;
			if(hit==0)
			{
				attackables[i]->damage(impactHit, slashHit, stabHit, brokeHit,  maxHit, soulHit, cause, source, canEmbed);
				return;
			}
		}

		std::cout << "Something went deadly wrong at unit damage randomness, hit is " << hit;
		World::me->pause();
	}

	soulHp-=soulHit;
	if(soulHp<=0 && initStatus!=2)
	{
		World::me->remUnit(this);
	}
}

int Unit::totalWeight() {
	if(brain!=NULL)
	{
		return brain->totalWeight();
	}

	int totalWeight=0;
	std::set<Item*> checked;

	std::set<Item*>::iterator next;
	for(next=parts.begin();next!=parts.end();next++)
	{
		if(checked.count(*next)==0)
		{
			std::vector<Item*> partBlob=(*next)->getBlob(1, 3, 1, 3, NULL, 0, 0);

			for(unsigned int i=0;i<partBlob.size();i++)
			{
				checked.insert(partBlob[i]);
				totalWeight+=partBlob[i]->weight;
			}
		}
	}

	return totalWeight;
}


bool Unit::connected(Item* obj, int attachlevel, int storedLevel, int holdingLevel, int embedLevel) {
	// attachLevel: 0 = ignore, 1 = search, -1 = search but must not be attached
	// storedLevel: 0 = ignore, 1 = things we're storing, 2 = things storing us, 3 = both, -1/2/3 = only if we're directly storing/stored by them
	// holdingLevel: 0 = ignore, 1 = things we're holding, 2 = things holding us, 3 = both, -1/2/3 = only if we're directly holding/held by them
	// embedLevel: 0 = ignore, 1 = things we embed into, 2 = things embedded into us, 3 = both, -1/2/3 = only if we're directly embedding/embedded by them

	if(brain!=NULL)
	{
		return brain->connected(obj, attachlevel, storedLevel, holdingLevel, embedLevel);
	}

	if(parts.empty())
	{
		return false;
	}

	return (*parts.begin())->connected(obj, attachlevel, storedLevel, holdingLevel, embedLevel);

	// TODO: even if no brain, all our parts should be connected so the below isnt needed?

//	std::set<Item*> organs(parts);
//	std::set<Item*>::iterator limb;
//	for(limb=organs.begin(); limb!=organs.end();limb++)
//	{
//		if((*limb)->connected(obj, attachedLevel))
//		{
//			return true;
//		}
//	}
//
//	return false;
}

void Unit::attach(Item* obj, bool isBrain) {
	// attach: adds obj to its list of parts, and sets as brain if isBrain. This should only be called from Item::attach or World::addItem
	// Attachtype should only be organ or brain
	// attached should only be called after being Unit::claimed. Currently happens manually in World::additem and should happen sometime before or during Item::attach
	//      ACTUALLY< the check just below has problems if claiming comes first, as the items aren't actually attched until the end of the Item::attach process, yet we check their claim early

	if(obj->bestCarryLevel(NULL)>=3 && obj->owner!=this)
	{
		std::cout << name(2) << " is trying to attach " << obj->name(2) << ", but its already armor / organ of its current owner " << obj->owner->name(2);
		World::me->pause();
	}

	std::vector<Item*> objBlob=obj->getBlob(1, 0, 0, 0, NULL, 0, 0);

	for(unsigned int i=0;i<objBlob.size();i++)
	{
		objBlob[i]->owner=this;
		parts.insert(objBlob[i]);
	}

	if(isBrain)
	{
		if(brain!=NULL)
		{
			std::cout << name(2) << " is trying to attach " << obj->name(2) << " as a brain, but we already have brain " << brain->name(2) << "? ";
			World::me->pause();
		}

		brain=obj;
	}
}

void Unit::detach(Item* obj, bool refreshNow) {
	// Opposite of attach; We remove this thing and its blob from our parts but handle the disowning part elsewhere

	std::vector<Item*> objBlob=obj->getBlob(1, 0, 0, 0, NULL, 0, 0);

	for(unsigned int i=0;i<objBlob.size();i++)
	{
		if(objBlob[i]->owner==NULL)
		{
			std::cout << "What the fug " << objBlob[i]->name(2) << " is being detached from me " << name(2) << " but has no owner?";
			World::me->pause();
		}

		objBlob[i]->owner=NULL;
		parts.erase(objBlob[i]);

		if(brain!=NULL && objBlob[i]==brain)
		{
			// Should be handled elsewhere in item::dead and such, correct?
		}
	}

	std::vector<Status*> afflictions(stati);
	for(unsigned int i=0;i<afflictions.size();i++)
	{
		afflictions[i]->disown(objBlob[i]);
	}

	if(parts.size()==0)
	{
		std::cout << "[" << name(2) << " was killed by having no more parts left!] ";
		World::me->remUnit(this);
	}
	else if(refreshNow)
	{
		World::me->handleRefresh();
	}
}

void Unit::sever(Item* obj, bool refreshNow) {
	// Unit sever: just finds what object it SHOULD be severed from, and make it call Item::sever from there. Should only really be called from Item::damage or World::remItem
	// should handle mechanically severing (removing it from parts, etc) in disown and such elsewhere

	if(obj->attached.empty())
	{
		std::cout << "!!!Error: Unit " << name(2) << " was told to sever sourceOrgan " << obj->name(2) << ", but it doesn't have any attached?";

		if(obj->initStatus==2)
		{
			std::cout << "[It is removed, but it shouldn't be calling sever tho] ";
		}

		World::me->pause();
	}

	if(brain==obj)
	{
		obj->sever(NULL, refreshNow);
		return;
	}
	else if(obj->bestCarryLevel(this)==3)
	{
		if(brain==NULL)
		{
			obj->sever(NULL, refreshNow);
			return;
		}

		// Breadth search for what part it gets torn off of
		std::list<Item*> remaining;
		std::set<Item*> checked;
		remaining.push_back(brain);
		checked.insert(brain);
		while(!remaining.empty())
		{
			Item* current=remaining.front();
			remaining.pop_front();

			std::set<Item*>::iterator next;
			for(next=current->attached.begin();next!=current->attached.end();next++)
			{
				if((*next)==obj)
				{
					current->sever(obj, refreshNow);
					return;
				}

				if(checked.count(*next)==0)
				{
					remaining.push_back(*next);
					checked.insert(*next);
				}
			}
		}

		std::cout << "!!!Error: Unit " << name(2) << " had its limb " << obj->name(2) << " severed, but it wasn't connected to any of his core parts?";
		World::me->pause();
	}
	else
	{
		obj->sever(NULL, refreshNow);
		return;
//		std::cout << "!!!Error: Unit " << name(2) << " told to sever " << obj->name(2) << ", but its not an organ so it shouldn't call sever?";
//		World::me->pause();
	}
}

void Unit::tryClaim(Item* obj, bool refreshNow) {
	// Only called from Item::attach BEFORE attaching, Item::grab/store, and initing item in world; in all cases we want to claim the entire blob

	if(obj->owner!=NULL && obj->owner!=this) // It's already someone else's organ, so the things we do below are already done / shouldn't happen
	{
		return;
	}

	int curBestClaim=obj->bestCarryLevel(NULL);

	if(curBestClaim==0) // If this thing is on the ground, pick it up into hidden land
	{
		std::vector<Item*> objBlob=obj->getBlob(1, 3, 3, 3, NULL, 0, 0);

		for(unsigned int i=0;i<objBlob.size();i++)
		{
			std::cout << "&" << name(2) << " claiming " << objBlob[i]->name(2) << "& " << std::endl;

			World::me->hideItem(objBlob[i], this);
		}
	}
	else if(curBestClaim!=3) // If its being held / stored, claim it by moving it to our square
	{
		std::vector<Item*> objBlob=obj->getBlob(1, 3, 3, 3, NULL, 0, 0);

		for(unsigned int i=0;i<objBlob.size();i++) // Even if another unit is holding it, its equal priority to us so who cares
		{
			World::me->moveItem(objBlob[i], xPos, yPos, zPos);
		}
	}
	// If its an organ, someone else owns it already. If its stored, we don't wanna move it when it's storage is somewhere else

	if(refreshNow)
	{
		World::me->handleRefresh();
	}
}

void Unit::drop(Item* obj, bool refreshNow) {
	// Obj can be an obj to make this guy drop it from all his hands, or null to make it drop everything it's holding at once

	if(obj!=NULL && obj->bestCarryLevel(this)!=2)
	{
		std::cout << "!!!Error: Unit " << name(2) << " was told to drop " << obj->name(2) << ", but its claim level is " << obj->bestCarryLevel(this) << "?";
		World::me->pause();
	}

	std::vector<Item*> myBlob=getBlob(true, 0, 0, 0, NULL, 0, 0);

	bool atLeastOne=false;
	for(unsigned int i=0;i<myBlob.size();i++)
	{
		if((obj!=NULL && myBlob[i]->holding==obj) || (obj==NULL && myBlob[i]->holding!=NULL))
		{
			myBlob[i]->drop(false);
			atLeastOne=true;
		}
	}

	if(!atLeastOne && obj!=NULL)
	{
		std::cout << "!!!Error: Unit " << name(2) << " was told to drop " << obj->name(2) << ", but it didn't drop it at all = never held it?";
		World::me->pause();
	}

	if(refreshNow)
	{
		World::me->handleRefresh();
	}
}

void Unit::dropped(Unit* dropper, bool refreshNow) {
	// dropper: NULL to get dropped by everyone holding this, or a specific unit to make only them drop us with anything they're holding us with

	std::vector<Item*> holdersBlob=getBlob(false, 0, -1, 3, this, -3, 0);

	for(unsigned int i=0;i<holdersBlob.size();i++)
	{
		if(holdersBlob[i]->owner==NULL)
		{
			std::cout << "how do we have holder " << holdersBlob[i]->name(2) << " holding " << " that has no owner? ";
			World::me->pause();
		}
		else if(dropper==NULL || holdersBlob[i]->owner==dropper)
		{
			holdersBlob[i]->drop(false);
		}
	}

	if(refreshNow)
	{
		World::me->handleRefresh();
	}
}

void Unit::dead(Item* obj) {
	// The object died on us, so force eject it. Rest is handled in World::remItem
	// We assume its a lone obj that's already severed everything attached to it

	if(obj->owner==this)
	{
		detach(obj, false);
		obj->disowned(false);
	}

	if(!obj->attached.empty())
	{
		std::cout << name(2) << " removing a dead " << obj->name(2) << ", but it still has attached parts?";
		World::me->pause();
	}

	if(brain==obj) // TODO: should this be moved to disown? we'd never ever sever our brain from ourselves, but maybe it could be disowned alone somehow???
	{
		std::cout << "[" << name(2) << " was killed by debraining!] ";
		World::me->remUnit(this);
	}

//	World::me->handleRefresh();		Handled elsewhere / later
}


std::vector<Item*> Unit::getBlob(bool includeBody, int storedLevel, int holdingLevel, int embedLevel, Unit* compareGuy, int ownerLevel, int activeLevel) {
	// includeBody: true = search and include attached, false = search over organ parts but dont include
	// storedLevel: 0 = ignore, 1 = things we're storing, 2 = anything storing us, 3 = both, -1/2/3 = only things directly being stored / storing us
	// holdingLevel: 0 = ignore, 1 = anything we're holding, 2 = anything holding us, 3 = both, -1/2/3 = only the parts we're directly holding / being held by
	// embedLevel: 0 = ignore, 1 = we embed into only, 2 = embedded into us only, 3 = both, -1/2/3 = only those directly embedded / embedding
	// compareGuy: whoever we want to use for checking if they're the "owner" below. AKA: find all the parts of a guy that someone is touching us with, and burn them specifically
	// ownerLevel: 0 = ignore, 1 = only save if the part isn't our organ, 2 = only save our / neutral parts, 3 = only save enemy organs, -1/2/3 = don't expand if we succeed a check
	// activeLevel: 0 = ignore, 1 = must be active, 2 = inactive usable (throw a broken gun), 3 = active usable (shoot a working gun), 4 = must be manipulable (type with a hand)

	if(brain!=NULL)
	{
		return brain->getBlob((includeBody ? 1 : -1), storedLevel, holdingLevel, embedLevel, compareGuy, ownerLevel, activeLevel);
	}

	std::vector<Item*> totalBlob;
	std::set<Item*> checked;

	std::set<Item*>::iterator next;
	for(next=parts.begin();next!=parts.end();next++)
	{
		if(checked.count(*next)==0)
		{
			std::vector<Item*> partBlob=(*next)->getBlob((includeBody ? 1 : -1), storedLevel, holdingLevel, embedLevel, compareGuy, ownerLevel, activeLevel);

			for(unsigned int i=0;i<partBlob.size();i++)
			{
				checked.insert(partBlob[i]);
				totalBlob.push_back(partBlob[i]);
			}
		}
	}

	return totalBlob;
}

std::vector<Unit*> Unit::connectedUnits() {
	// Every other unit we're directly holding or being held by (maybe a guy we're holding is holding someone else, etc)

	std::vector<Item*> myBlob=getBlob(false, 0, -3, -3, this, -3, 0);
	std::vector<Unit*> totalUnits;
	std::set<Unit*> checked;

	for(unsigned int i=0;i<myBlob.size();i++)
	{
		if(myBlob[i]->owner!=NULL && myBlob[i]->owner!=this && checked.count(myBlob[i]->owner)==0)
		{
			checked.insert(myBlob[i]->owner);
			totalUnits.push_back(myBlob[i]->owner);
		}
	}

	return totalUnits;
}

std::vector<Living*> Unit::refreshBlob() {
	// All parts, all held blobs, all blobs of everyone we're connected with indirectly via hand holding, and all stati on everything

	std::vector<Living*> myBlob;
	if(brain!=NULL)
	{
		myBlob=brain->refreshBlob();
	}
	else
	{
		std::set<Living*> checked;

		std::set<Item*>::iterator limb;
		for(limb=parts.begin(); limb!=parts.end();limb++)
		{
			if(checked.count(*limb)==0)
			{
				std::vector<Living*> limbBlob=(*limb)->refreshBlob();

				for(unsigned int i=0;i<limbBlob.size();i++)
				{
					if(checked.count(limbBlob[i])==0)
					{
						checked.insert(limbBlob[i]);
						myBlob.push_back(limbBlob[i]);
					}
				}
			}
		}
	}

	myBlob.push_back(this);

	for(unsigned int i=0; i<stati.size(); i++)
	{
		myBlob.push_back(stati[i]);
	}

	if(myGrav!=NULL)
	{
		myBlob.push_back(myGrav);
	}

	return myBlob;
}


int Unit::count(std::string name, ItemTag tagType, bool includeBody, int storedLevel, int holdingLevel, int embedLevel, Unit* compareGuy, int ownerLevel, int activeLevel) {
	return getParts(name, tagType, includeBody, storedLevel, holdingLevel, embedLevel, compareGuy, ownerLevel, activeLevel).size();
}

Item* Unit::getPart(std::string name, ItemTag tagType, bool includeBody, int storedLevel, int holdingLevel, int embedLevel, Unit* compareGuy, int ownerLevel, int activeLevel) {
	if(brain!=NULL)
	{
		return brain->getPart(name, tagType, (includeBody ? 1 : -1), storedLevel, holdingLevel, embedLevel, compareGuy, ownerLevel, activeLevel);
	}

	std::vector<Item*> myBlob=getBlob(includeBody, storedLevel, holdingLevel, embedLevel, compareGuy, ownerLevel, activeLevel);
	for(unsigned int i=0;i<myBlob.size();i++)
	{
		if((name=="" || myBlob[i]->species==name) &&
			(tagType==NULL_ITEM_TAG || myBlob[i]->selfTags.count(tagType)!=0))
		{
			return myBlob[i];
		}
	}

	return NULL;
}

std::vector<Item*> Unit::getParts(std::string name, ItemTag tagType, bool includeBody, int storedLevel, int holdingLevel, int embedLevel, Unit* compareGuy, int ownerLevel, int activeLevel) {
	if(brain!=NULL)
	{
		return brain->getParts(name, tagType, (includeBody ? 1 : -1), storedLevel, holdingLevel, embedLevel, compareGuy, ownerLevel, activeLevel);
	}

	std::vector<Item*> results;

	std::vector<Item*> myBlob=getBlob(includeBody, storedLevel, holdingLevel, embedLevel, compareGuy, ownerLevel, activeLevel);
	for(unsigned int i=0;i<myBlob.size();i++)
	{
		if((name=="" || myBlob[i]->species==name) &&
			(tagType==NULL_ITEM_TAG || myBlob[i]->selfTags.count(tagType)!=0))
		{
			results.push_back(myBlob[i]);
		}
	}

	return results;
}


Actool* Unit::getActool(std::string name, ActionTag type, ActionSubtag subType, int possibleLevel) {
	// TODO: if getActions becomes complicated, make this just get that vector value and search through the given actions inseatd of searching below

	Actool* bestActool=NULL;

	for(unsigned int i=0;i<addedActions.size();i++)
	{
		if((name=="" || addedActions[i]->actionName==name) &&
			(type==NULL_ACTION_TAG || addedActions[i]->actionType==type) &&
			(subType==NULL_ACTION_SUBTAG || addedActions[i]->actionSubtype==subType))
		{
			std::vector<Actool*> results=addedActions[i]->getActools(this, possibleLevel);
			for(unsigned int j=0;j<results.size();j++)
			{
				if(bestActool==NULL || results[j]->getValue()>bestActool->getValue())
				{
					// TODO: delete old actool
					bestActool=results[j];
				}
			}
		}
	}


	std::vector<Item*> checkList=getBlob(true, 0, -1, 0, NULL, 0, 0); // TODO: Our body + thing's we're holding are our only potentialy usable items, correct?

	for(unsigned int i=0;i<checkList.size();i++)
	{
		for(unsigned int j=0;j<checkList[i]->addedActions.size();j++)
		{
			if((name=="" || checkList[i]->addedActions[j]->actionName==name) &&
				(type==NULL_ACTION_TAG || checkList[i]->addedActions[j]->actionType==type) &&
				(subType==NULL_ACTION_SUBTAG || checkList[i]->addedActions[j]->actionSubtype==subType))
			{
				std::vector<Actool*> results=checkList[i]->addedActions[j]->getActools(this, possibleLevel);

				for(unsigned int k=0;k<results.size();k++)
				{
					if(bestActool==NULL || results[k]->getValue()>bestActool->getValue())
					{
						bestActool=results[k];
					}
				}
			}
		}

		for(unsigned int j=0;j<checkList[i]->selfActions.size();j++)
		{
			if((name=="" || checkList[i]->selfActions[j]->actionName==name) &&
				(type==NULL_ACTION_TAG || checkList[i]->selfActions[j]->actionType==type) &&
				(subType==NULL_ACTION_SUBTAG || checkList[i]->selfActions[j]->actionSubtype==subType))
			{
				Actool* result=checkList[i]->selfActions[j]->getActool(checkList[i], this, possibleLevel);

				if(result!=NULL && (bestActool==NULL || result->getValue()>bestActool->getValue()))
				{
					bestActool=result;
				}

				result=checkList[i]->selfActions[j]->getActool(NULL, this, possibleLevel);

				if(result!=NULL && (bestActool==NULL || result->getValue()>bestActool->getValue()))
				{
					bestActool=result;
				}
			}
		}
	}

	return bestActool;
}

Actool* Unit::getActool(std::string name, ActionTag type, ActionSubtag subType, Unit* uTarget, Item* iTarget, Square* sTarget) {
	// TODO: if getActions becomes complicated, make this just get that vector value and search through the given actions inseatd of searching below

	Actool* bestActool=NULL;

	for(unsigned int i=0;i<addedActions.size();i++)
	{
		if((name=="" || addedActions[i]->actionName==name) &&
			(type==NULL_ACTION_TAG || addedActions[i]->actionType==type) &&
			(subType==NULL_ACTION_SUBTAG || addedActions[i]->actionSubtype==subType))
		{
			std::vector<Actool*> results=addedActions[i]->getActools(this, 2);
			for(unsigned int j=0;j<results.size();j++)
			{
				if(results[j]->canAttempt(uTarget, iTarget, sTarget) &&
					(bestActool==NULL || results[j]->getValue()>bestActool->getValue()))
				{
					// TODO: delete old actool
					bestActool=results[j];
				}
			}
		}
	}


	std::vector<Item*> checkList=getBlob(true, 0, -1, 0, NULL, 0, 0); // TODO: Our body + thing's we're holding are our only potentialy usable items, correct?

	for(unsigned int i=0;i<checkList.size();i++)
	{
		for(unsigned int j=0;j<checkList[i]->addedActions.size();j++)
		{
			if((name=="" || checkList[i]->addedActions[j]->actionName==name) &&
				(type==NULL_ACTION_TAG || checkList[i]->addedActions[j]->actionType==type) &&
				(subType==NULL_ACTION_SUBTAG || checkList[i]->addedActions[j]->actionSubtype==subType))
			{
				std::vector<Actool*> results=checkList[i]->addedActions[j]->getActools(this, 2);

				for(unsigned int k=0;k<results.size();k++)
				{
					if(results[k]->canAttempt(uTarget, iTarget, sTarget) &&
						(bestActool==NULL || results[k]->getValue()>bestActool->getValue()))
					{
						bestActool=results[k];
					}
				}
			}
		}

		for(unsigned int j=0;j<checkList[i]->selfActions.size();j++)
		{
			if((name=="" || checkList[i]->selfActions[j]->actionName==name) &&
				(type==NULL_ACTION_TAG || checkList[i]->selfActions[j]->actionType==type) &&
				(subType==NULL_ACTION_SUBTAG || checkList[i]->selfActions[j]->actionSubtype==subType))
			{
				Actool* result=checkList[i]->selfActions[j]->getActool(checkList[i], this, 2);

				if(result!=NULL && result->canAttempt(uTarget, iTarget, sTarget) &&
					(bestActool==NULL || result->getValue()>bestActool->getValue()))
				{
					bestActool=result;
				}

				result=checkList[i]->selfActions[j]->getActool(NULL, this, 2);

				if(result!=NULL && result->canAttempt(uTarget, iTarget, sTarget) &&
					(bestActool==NULL || result->getValue()>bestActool->getValue()))
				{
					bestActool=result;
				}
			}
		}
	}

	return bestActool;
}

std::vector<Actool*> Unit::getActools(std::string name, ActionTag type, ActionSubtag subType, int possibleLevel) {
	// possibleLevel: -1 = not valid at all (can't grab with a sword / NULL tool), 0 = possible but not usable (can't grab if already holding), 1 = possible (empty hand), 2 = possible w/ targets

	std::vector<Actool*> actoolList;

	for(unsigned int i=0;i<addedActions.size();i++)
	{
		if((name!="" && addedActions[i]->actionName!=name) ||
			(type!=NULL_ACTION_TAG && addedActions[i]->actionType!=type) ||
			(subType!=NULL_ACTION_SUBTAG && addedActions[i]->actionSubtype!=subType))
		{
			continue;
		}

		std::vector<Actool*> newActools=addedActions[i]->getActools(this, possibleLevel);
		for(unsigned int j=0;j<newActools.size();j++)
		{
			actoolList.push_back(newActools[j]);

			if(actoolList.size()<=1)
			{
				continue;
			}

			Actool* temp=newActools[j];

			int k=actoolList.size()-2;
			while(k>=0 && actoolList[k]->getValue() < actoolList[k+1]->getValue())
			{
				temp=actoolList[k];
				actoolList[k]=actoolList[k+1];
				actoolList[k+1]=temp;
				k--;
			}
		}
	}


	std::vector<Item*> checkList=getBlob(true, 0, -1, 0, NULL, 0, 0);

	for(unsigned int i=0;i<checkList.size();i++)
	{
		for(unsigned int j=0;j<checkList[i]->addedActions.size();j++)
		{
			if((name!="" && checkList[i]->addedActions[j]->actionName!=name) ||
				(type!=NULL_ACTION_TAG && checkList[i]->addedActions[j]->actionType!=type) ||
				(subType!=NULL_ACTION_SUBTAG && checkList[i]->addedActions[j]->actionSubtype!=subType))
			{
				continue;
			}

			std::vector<Actool*> addedActools=checkList[i]->addedActions[j]->getActools(this, possibleLevel);

			for(unsigned int k=0;k<addedActools.size();k++)
			{
				actoolList.push_back(addedActools[k]);

				if(actoolList.size()<=1)
				{
					continue;
				}

				Actool* temp=addedActools[k];

				int l=actoolList.size()-2;
				while(l>=0 && actoolList[l]->getValue() < actoolList[l+1]->getValue())
				{
					temp=actoolList[l];
					actoolList[l]=actoolList[l+1];
					actoolList[l+1]=temp;
					l--;
				}
			}
		}

		for(unsigned int j=0;j<checkList[i]->selfActions.size();j++)
		{
			if((name!="" && checkList[i]->selfActions[j]->actionName!=name) ||
				(type!=NULL_ACTION_TAG && checkList[i]->selfActions[j]->actionType!=type) ||
				(subType!=NULL_ACTION_SUBTAG && checkList[i]->selfActions[j]->actionSubtype!=subType))
			{
				continue;
			}

			Actool* result=checkList[i]->selfActions[j]->getActool(checkList[i], this, possibleLevel);

			if(result!=NULL)
			{
				actoolList.push_back(result);

				if(actoolList.size()<=1)
				{
					continue;
				}

				Actool* temp=result;

				int k=actoolList.size()-2;
				while(k>=0 && actoolList[k]->getValue() < actoolList[k+1]->getValue())
				{
					temp=actoolList[k];
					actoolList[k]=actoolList[k+1];
					actoolList[k+1]=temp;
					k--;
				}
			}

			result=checkList[i]->selfActions[j]->getActool(NULL, this, possibleLevel);

			if(result!=NULL)
			{
				actoolList.push_back(result);

				if(actoolList.size()<=1)
				{
					continue;
				}

				Actool* temp=result;

				int k=actoolList.size()-2;
				while(k>=0 && actoolList[k]->getValue() < actoolList[k+1]->getValue())
				{
					temp=actoolList[k];
					actoolList[k]=actoolList[k+1];
					actoolList[k+1]=temp;
					k--;
				}
			}
		}
	}

	return actoolList;
}

Action* Unit::getAction(std::string name, ActionTag type, ActionSubtag subType, int possibleLevel) {
	// Returns the first action we find that fits the parameters, as we can't calculate value without a tool

	Actool* result=getActool(name, type, subType, possibleLevel);

	if(result!=NULL)
	{
		return result->act;
	}

	return NULL;

	// TODO: we can't get the best value'd action without doing above, but if we dont care for value the below works slightly faster

//	for(unsigned int i=0;i<addedActions.size();i++)
//	{
//		if((name=="" || addedActions[i]->actionName==name) &&
//			(type==NULL_ACTION_TAG || addedActions[i]->actionType==type) &&
//			(subType==NULL_ACTION_SUBTAG || addedActions[i]->actionSubtype==subType) &&
//			(!onlyPossible || !addedActions[i]->getActools(this, true).empty()))
//		{
//			return addedActions[i];
//		}
//	}
//
//
//	std::vector<Item*> checkList=getBlob(true, true, -1, 0, 0);
//
//	for(unsigned int i=0;i<checkList.size();i++)
//	{
//		for(unsigned int j=0;j<checkList[i]->addedActions.size();j++)
//		{
////			std::cout << "checking " << checkList[i]->name(2) << "'s added action " << checkList[i]->addedActions[j]->actionName << std::endl;
//
//			if((name=="" || checkList[i]->addedActions[j]->actionName==name) &&
//				(type==NULL_ACTION_TAG || checkList[i]->addedActions[j]->actionType==type) &&
//				(subType==NULL_ACTION_SUBTAG || checkList[i]->addedActions[j]->actionSubtype==subType) &&
//				(!onlyPossible || checkList[i]->addedActions[j]->canTryAttempt(NULL, this)))
//			{
//				if(checkList[i]->addedActions[j]->value>curValue)
//				{
//					curValue=checkList[i]->addedActions[j]->value;
//					bestAct=checkList[i]->addedActions[j];
//				}
//			}
//		}
//
//		for(unsigned int j=0;j<checkList[i]->selfActions.size();j++)
//		{
////			std::cout << "checking " << checkList[i]->name(2) << "'s self action " << checkList[i]->selfActions[j]->actionName << std::endl;
//
//			if((name=="" || checkList[i]->selfActions[j]->actionName==name) &&
//				(type==NULL_ACTION_TAG || checkList[i]->selfActions[j]->actionType==type) &&
//				(subType==NULL_ACTION_SUBTAG || checkList[i]->selfActions[j]->actionSubtype==subType) &&
//				(!onlyPossible || checkList[i]->selfActions[j]->canTryAttempt(checkList[i], this)))
//			{
//				if(checkList[i]->selfActions[j]->value>curValue)
//				{
//					curValue=checkList[i]->selfActions[j]->value;
//					bestAct=checkList[i]->selfActions[j];
//				}
//			}
//		}
//	}
//
//	return bestAct;
}

std::vector<Action*> Unit::getActions(std::string name, ActionTag type, ActionSubtag subType, int possibleLevel) {
	// NOT returned in value order: taught actions won't have exact values

	std::vector<Action*> actionList;

	for(unsigned int i=0;i<addedActions.size();i++)
	{
		if((name!="" && addedActions[i]->actionName!=name) ||
			(type!=NULL_ACTION_TAG && addedActions[i]->actionType!=type) ||
			(subType!=NULL_ACTION_SUBTAG && addedActions[i]->actionSubtype!=subType) ||
			(possibleLevel>=0 && addedActions[i]->getActools(this, possibleLevel).empty()))
		{
			continue;
		}

		actionList.push_back(addedActions[i]);

//		if(actionList.size()<=1)
//		{
//			continue;
//		}
//
//		Action* temp=actionList[i];
//
//		int j=actionList.size()-2;
//		while(j>=0 && actionList[j]->getValue() < actionList[j+1]->getValue())
//		{
//			temp=actionList[j];
//			actionList[j]=actionList[j+1];
//			actionList[j+1]=temp;
//			j--;
//		}
	}


	std::vector<Item*> checkList=getBlob(true, 0, -1, 0, NULL, 0, 0); // TODO: Our body + thing's we're holding are our only potentialy usable items, correct?

	for(unsigned int i=0;i<checkList.size();i++)
	{
		for(unsigned int j=0;j<checkList[i]->addedActions.size();j++)
		{
			if((name!="" && checkList[i]->addedActions[j]->actionName!=name) ||
				(type!=NULL_ACTION_TAG && checkList[i]->addedActions[j]->actionType!=type) ||
				(subType!=NULL_ACTION_SUBTAG && checkList[i]->addedActions[j]->actionSubtype!=subType) ||
				(possibleLevel>=0 && checkList[i]->addedActions[j]->getActools(this, possibleLevel).empty()))
			{
				continue;
			}

			actionList.push_back(checkList[i]->addedActions[j]);

//			if(actionList.size()<=1)
//			{
//				continue;
//			}
//
//			Action* temp=checkList[i]->addedActions[j];
//
//			int k=actionList.size()-2;
//			while(k>=0 && actionList[k]->value < actionList[k+1]->value)
//			{
//				temp=actionList[k];
//				actionList[k]=actionList[k+1];
//				actionList[k+1]=temp;
//				k--;
//			}
		}

		for(unsigned int j=0;j<checkList[i]->selfActions.size();j++)
		{
			if((name=="" || checkList[i]->selfActions[j]->actionName!=name) &&
				(type==NULL_ACTION_TAG || checkList[i]->selfActions[j]->actionType!=type) &&
				(subType==NULL_ACTION_SUBTAG || checkList[i]->selfActions[j]->actionSubtype!=subType) &&
				(possibleLevel<0 || checkList[i]->selfActions[j]->getActool(checkList[i], this, possibleLevel)!=NULL || checkList[i]->selfActions[j]->getActool(NULL, this, possibleLevel)!=NULL))
			{
				actionList.push_back(checkList[i]->selfActions[j]);
			}


//			if(actionList.size()<=1)
//			{
//				continue;
//			}
//
//			Action* temp=checkList[i]->selfActions[j];
//
//			int k=actionList.size()-2;
//			while(k>=0 && actionList[k]->value < actionList[k+1]->value)
//			{
//				temp=actionList[k];
//				actionList[k]=actionList[k+1];
//				actionList[k+1]=temp;
//				k--;
//			}
		}
	}

	return actionList;
}

Task* Unit::getTask(std::string name) {
	for(unsigned int i=0;i<addedTasks.size();i++)
	{
		if((name=="" || addedTasks[i]->taskName==name))
		{
			return addedTasks[i];
		}
	}

	std::vector<Item*> checkList=getBlob(true, -1, -1, -3, NULL, 0, 0); // TODO: what should we search for tasks from? it could literally be anything in the game world

	for(unsigned int i=0;i<checkList.size();i++)
	{
		for(unsigned int j=0;j<checkList[i]->addedTasks.size();j++)
		{
			if(name=="" || checkList[i]->addedTasks[j]->taskName==name)
			{
				return checkList[i]->addedTasks[j];
			}
		}
	}

	return NULL;
}

std::vector<Task*> Unit::getTasks(std::string name) {
	std::vector<Task*> taskList;

	for(unsigned int i=0;i<addedTasks.size();i++)
	{
		if(name!="" && addedTasks[i]->taskName!=name)
		{
			continue;
		}

		taskList.push_back(addedTasks[i]);

		if(taskList.size()<=1)
		{
			continue;
		}

		Task* temp=addedTasks[i];

		int j=taskList.size()-2;
		while(j>=0 && taskList[j]->priority > taskList[j+1]->priority)
		{
			temp=taskList[j];
			taskList[j]=taskList[j+1];
			taskList[j+1]=temp;
			j--;
		}
	}


	std::vector<Item*> checkList=getBlob(true, -1, -1, -3, NULL, 0, 0);

	for(unsigned int i=0;i<checkList.size();i++)
	{
		for(unsigned int j=0;j<checkList[i]->addedTasks.size();j++)
		{
			if(name!="" && checkList[i]->addedTasks[j]->taskName!=name)
			{
				continue;
			}

			taskList.push_back(checkList[i]->addedTasks[j]);

			if(taskList.size()<=1)
			{
				continue;
			}

			Task* temp=checkList[i]->addedTasks[j];

			int k=taskList.size()-2;
			while(k>=0 && taskList[k]->priority > taskList[k+1]->priority)
			{
				temp=taskList[k];
				taskList[k]=taskList[k+1];
				taskList[k+1]=temp;
				k--;
			}
		}
	}

	return taskList;
}

void Unit::interrupt(int severity) {

}

void Unit::fullRefresh() {
	retag(NULL);

	std::vector<Living*> myBlob=refreshBlob();
	for(unsigned int i=0;i<myBlob.size();i++)
	{
		if(!myBlob[i]->refresh())
		{
			fullRefresh();
			return;
		}
	}
}

bool Unit::refresh() {
	if(initStatus==2)
	{
		return true;
	}

	bool allClear=true;

	if(myGrav==NULL && fallCheck())
	{
		std::cout << " (" << name(2) << " started to unitfall!) ";
		World::me->addGravity(new Gravity(this));
		drop(NULL, true);
		allClear=false;
	}

//	if(activeActool!=NULL && activeActool->howPossible()<=1)   TODO: put this in interrupt? shouldn't be here I think, resets it correctly but randomly
//	{
//		std::cout << " (" << name(2) << " had its active act " << activeActool->act->actionName << " cancled!) ";
//		activeActool=NULL;
//		activeUTarget=NULL;
//		activeITarget=NULL;
//		activeSTarget=NULL;
//		energy=10;
//		World::me->activeQueue.update(this);
//		allClear=false;
//	}

	return allClear;
}

void Unit::retag(std::multiset<Tag>* sharedTags) {
	std::multiset<Tag> extraTags;

	if(sharedTags==NULL)
	{
		extraTags.insert(duoTags.begin(), duoTags.end());

		std::vector<Status*> afflictions(stati);
		for(unsigned int i=0;i<afflictions.size();i++)
		{
			extraTags.insert(afflictions[i]->duoTags.begin(), afflictions[i]->duoTags.end());
		}

		std::vector<Living*> myBlob=refreshBlob();
		for(unsigned int i=0;i<myBlob.size();i++)
		{
			if(myBlob[i]->order==STATUS)
			{
				Status* effect=dynamic_cast<Status*>(myBlob[i]);
				extraTags.insert(effect->duoTags.begin(), effect->duoTags.end());
			}
			else if(myBlob[i]->order==ITEM)
			{
				Item* obj=dynamic_cast<Item*>(myBlob[i]);
				extraTags.insert(obj->duoTags.begin(), obj->duoTags.end());

				if(obj->isActive())
				{
					if(obj->bestCarryLevel(this)==3)
					{
						extraTags.insert(obj->organTags.begin(), obj->organTags.end());
					}
					else if(obj->bestCarryLevel(this)==2)
					{
						extraTags.insert(obj->heldTags.begin(), obj->heldTags.end());
					}
				}
			}
		}

	}
	else
	{
		extraTags=*sharedTags;
	}


	tags.clear();
	tags.insert(soloTags.begin(), soloTags.end());

	std::vector<Status*> afflictions(stati);
	for(unsigned int i=0;i<afflictions.size();i++)
	{
		tags.insert(afflictions[i]->soloTags.begin(), afflictions[i]->soloTags.end());
	}

	tags.insert(extraTags.begin(), extraTags.end());


	if(sharedTags==NULL)
	{
		std::set<Item*> organs(parts);
		std::set<Item*>::iterator limb;
		for(limb=organs.begin(); limb!=organs.end();limb++)
		{
			(*limb)->retag(&extraTags);
		}
	}
	else
	{
		std::cout << "Why is " << name(2) << " retagging with already given tags?" << std::endl;
		World::me->pause();
	}
}


void Unit::tryDie() {
	std::vector<Living*> myBlob=refreshBlob();
	for(unsigned int i=0;i<myBlob.size();i++)
	{
		if(myBlob[i]->order==STATUS)
		{
			Status* effect=dynamic_cast<Status*>(myBlob[i]);
			if(!effect->letDie(this))
			{
				return;
			}
		}
		else if(myBlob[i]->order==ITEM)
		{
			Item* obj=dynamic_cast<Item*>(myBlob[i]);

			if(!obj->letDie(this))
			{
				return;
			}
		}
	}

	std::cout << "[" << name(2) << " was killed!] ";
	World::me->remUnit(this);
}



std::string Unit::name(int detail) {
	// 0 = just species + id, 1 = + location, 2 = + info on owned items

	if(detail==0)
	{
		return species + " " + std::to_string(id);
	}
	else if(detail==1)
	{

		return species + " " + std::to_string(id) + " (" + std::to_string(xPos) + " " + std::to_string(yPos) + " " + std::to_string(zPos) + ")";
	}
	else
	{
		std::string finalName=species + " " + std::to_string(id) + " (" + std::to_string(xPos) + " " + std::to_string(yPos) + ") {";

		std::set<Item*>::iterator organs;
		for(organs=parts.begin(); organs!=parts.end(); organs++)
		{
			finalName = finalName + (*organs)->name(0) + " ";
		}

		finalName = finalName + "} ";

		return finalName;
	}
}
