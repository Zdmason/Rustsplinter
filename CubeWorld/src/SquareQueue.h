
#ifndef SQUAREQUEUE_H_
#define SQUAREQUEUE_H_

#include "Square.h"

#include <vector>

class SquareQueue {
public:
	SquareQueue();
	//~SquareQueue();

	std::vector<Square*> myVec;

	void push(Square* newSquare);
	void pop();
	Square* front();
	int size();
	void update(Square* oddSquare);
	void update();
};

#endif /* SQUAREQUEUE_H_ */
