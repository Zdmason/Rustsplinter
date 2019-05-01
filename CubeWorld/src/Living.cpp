
#include "Living.h"
#include "World.h"

#include <iostream>
#include <cstdio>

Living::Living() {
	order=LIVING;
	//family=INIT;
	//genus=NONE;
	species="Null";
	id=World::me->curId;
	World::me->curId++;

	isAlive=false;
	initStatus=0;
	speed=1000;
	energy=id+5; //TODO: remove when energy is correct / real
}

Living::~Living() {
	;
}

//void Living::age(int time) {
//	;
//}

void Living::update() {
	std::cout << "!!! Living's version of update is being called when it should be overwritten?";
	World::me->pause();

}

void Living::work() {
	std::cout << "!!! Living's version of work is being called when it should be overwritten?";
	World::me->pause();
}

bool Living::letMove(int x, int y, int z) {
	return true;
}

void Living::fullRefresh() {
	std::cout << "!!! Living's version of fullRefresh is being called when it should be overwritten?";
	World::me->pause();
}

bool Living::refresh() {
	std::cout << "!!! Living's version of refresh is being called when it should be overwritten?";
	World::me->pause();
	return false;
}


std::string Living::name(int detail) {
	// 0 = just species + id, 1 = + location, 2 = + info on owner / owned items
	return species + " " + std::to_string(id);
}
