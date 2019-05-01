
#include "../Entities/Units/Unit.h"
#include "Status.h"
#include "../World.h"

#include <iostream>

Status::Status() : Living() {
	order=STATUS;

	// soloTags initialized as empty vector
	// duoTags initialized as empty vector
	duration=-1;
	priority=-1;
	victim=NULL;
	encompassing=false;
}

Status::~Status() {
	; // TODO: make this
}


void Status::copy(Entity* newVictim) {
	std::cout << "Please make a copy function for status type " << species;
	World::me->pause();
}


void Status::update() {
	std::cout << name(2) << " (" << victim->name(2) << ") : ";

	if(energy!=0)
	{
		std::cout << "??? " << name(2) << " updating even though my energy is " << energy << "???" << std::endl;
		World::me->pause();
	}

	if(victim==NULL)
	{
		std::cout << "??? I'm updating even though my victim is gone???" << std::endl;
		World::me->pause();
	}
	if(victim->initStatus==2)
	{
		std::cout << "??? I'm updating even though my victim is dead???" << std::endl;
		World::me->pause();
	}

	work();

	energy=speed;
	std::cout << std::endl;
}

void Status::work() {
	duration--;
	std::cout << duration << " turns left";
	if(duration<=0)
	{
		expire();
	}
}

void Status::subwork() {
	;
}


/*
void Status::move() {
	;
}

int Status::attack(int amount, Distance distance, Method method, Unit* target) {
	return amount;
}

int Status::damage(int amount, Distance distance, Method method, Unit* attacker) {
	return amount;
}

void Status::shake() {
	;
}
*/


bool Status::letInfect(Status* effect) {
	return true;
}

void Status::onInfect() {

}

void Status::blocked() {
	std::cout << "[" << name(2) << " was blocked!]";
}

void Status::fullRefresh() {
	victim->fullRefresh();
}

bool Status::refresh() {
	return true;
}

void Status::dispell() {
	std::cout << "[" << name(2) << " was dispelled!]";
	World::me->remStatus(this);
}

void Status::expire() {
	std::cout << "[" << name(2) << " expired!]";
	World::me->remStatus(this);
}

void Status::dead(Entity* thing) {
	std::cout << "[" << name(2) << " was removed when its victim died!]";
	World::me->remStatus(this);
}

void Status::disown(Entity* thing) {
	if(encompassing)
	{
		copy(thing);
	}
}

void Status::onDie() {
	;
}


bool Status::letDie(Entity* thing) {
	return true;
}
