
#include "Task.h"
#include "..\Actions\Action.h"
#include "..\World.h"

Task::Task() {
	id=World::me->curId;
	World::me->curId++;

	taskName="Task";
	priority=-1;
}

Task::~Task() {
	; // TODO: make this / replace die()?
}


bool Task::attempt(Unit* taskMaster) {
	// Returns true if we did something, false if we didn't and should try the next task

	std::cout << "Task " << taskName << " didn't make its own attempt?";
	World::me->pause();
	return false;
}
