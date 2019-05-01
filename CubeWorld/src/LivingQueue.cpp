
#include "LivingQueue.h"

#include <iostream>

LivingQueue::LivingQueue() {
	// myVec init as empty vector

	// myVec stores all the living from highest front to lowest back.
	// IE, the opposite of a normal queue : 10  7  4  2  1
	// "front" just takes the one at the end, 1
}

void LivingQueue::push(Living* newLiving) {
	myVec.push_back(newLiving);
//	std::cout << "Adding a " << newLiving->species << " " << newLiving->id << " " << newLiving->energy << std::endl;

	if(myVec.size()<=1)
	{
		return;
	}

	Living* temp=newLiving;
	int i=myVec.size()-2;
	while(i>=0 && (myVec[i]->energy < myVec[i+1]->energy || (myVec[i]->energy==myVec[i+1]->energy && myVec[i]->id < myVec[i+1]->id)))
	{
		temp=myVec[i];
		myVec[i]=myVec[i+1];
		myVec[i+1]=temp;
		i--;
	}

//	std::cout << "back is " << myVec[0]->species << " " << myVec[0]->id << " " << myVec[0]->energy << std::endl;
//	std::cout << "next is " << myVec[1]->species << " " << myVec[1]->id << " " << myVec[1]->energy << std::endl;
}

void LivingQueue::pop() {
	myVec.pop_back();
}

Living* LivingQueue::front() {
	return myVec.back();
}

int LivingQueue::size() {
	return myVec.size();
}

void LivingQueue::update(Living* oddLiving) {
	if(myVec.size()<=1)
	{
		return;
	}

	Living* temp;
	for(unsigned int i=0;i<myVec.size();i++)
	{
		if(myVec[i]==oddLiving)
		{
			while(i<myVec.size()-1 && (myVec[i]->energy < myVec[i+1]->energy || (myVec[i]->energy==myVec[i+1]->energy && myVec[i]->id < myVec[i+1]->id)))
			{
				temp=myVec[i];
				myVec[i]=myVec[i+1];
				myVec[i+1]=temp;
				i++;
			}
			while(i>=1 && (myVec[i-1]->energy < myVec[i]->energy || (myVec[i-1]->energy==myVec[i]->energy && myVec[i-1]->id < myVec[i]->id)))
			{
				temp=myVec[i-1];
				myVec[i-1]=myVec[i];
				myVec[i]=temp;
				i--;
			}
			return;
		}
	}
}
void LivingQueue::update() {
	if(myVec.size()<=1)
	{
		return;
	}

	bool working=true;
	Living* temp;
	while(working)
	{
		working=false;
		for(unsigned int i=0;i<myVec.size()-1;i++)
		{
			if(myVec[i]->energy < myVec[i+1]->energy || (myVec[i]->energy==myVec[i+1]->energy && myVec[i]->id < myVec[i+1]->id))
			{
				temp=myVec[i];
				myVec[i]=myVec[i+1];
				myVec[i+1]=temp;
				working=true;
			}
		}
	}
}
