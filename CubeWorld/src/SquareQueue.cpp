
#include "SquareQueue.h"

#include <iostream>

SquareQueue::SquareQueue() {
	// myVec init as empty vector

	// myVec stores all the squares from highest front to lowest back.
	// IE, the opposite of a normal queue : 10  7  4  2  1
}

void SquareQueue::push(Square* newSquare) {
	myVec.push_back(newSquare);

	if(myVec.size()<=1)
	{
		return;
	}

	Square* temp=newSquare;
	for(int i=myVec.size()-2;i>=0;i--)
	{
		if((myVec[i]->steps + myVec[i]->estDist) < (myVec[i+1]->steps + myVec[i+1]->estDist))
		{
			temp=myVec[i];
			myVec[i]=myVec[i+1];
			myVec[i+1]=temp;
		}
		else
		{
			i=-1;
		}
	}
}

void SquareQueue::pop() {
	myVec.pop_back();
}

Square* SquareQueue::front() {
	return myVec.back();
}

int SquareQueue::size() {
	return myVec.size();
}

void SquareQueue::update(Square* oddSquare) {
	if(myVec.size()<=1)
	{
		return;
	}

	Square* temp;
	for(unsigned int i=0;i<myVec.size();i++)
	{
		if(myVec[i]==oddSquare)
		{
			while(i<myVec.size()-1 && ((myVec[i]->steps + myVec[i]->estDist) < (myVec[i+1]->steps + myVec[i+1]->estDist)))
			{
				temp=myVec[i];
				myVec[i]=myVec[i+1];
				myVec[i+1]=temp;
				i++;
			}
			while(i>=1 && ((myVec[i-1]->steps + myVec[i-1]->estDist) < (myVec[i]->steps + myVec[i]->estDist)))
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
void SquareQueue::update() {
	if(myVec.size()<=1)
	{
		return;
	}

	// TODO: Is bubble sort needed? is it best on average? what cases do we need for just square pathing?
	bool working=true;
	Square* temp;
	while(working)
	{
		working=false;
		for(unsigned int i=0;i<myVec.size()-1;i++)
		{
			if((myVec[i]->steps + myVec[i]->estDist) < (myVec[i+1]->steps + myVec[i+1]->estDist))
			{
				temp=myVec[i];
				myVec[i]=myVec[i+1];
				myVec[i+1]=temp;
				working=true;
			}
		}
	}
}
