#pragma once

#include "Block.h"
#include "Operator.h"

/**
Algorithm class contains a block with the actual connections between operators
and the operator pointers themselves so that we can delete them when they get
necessary.
*/
class Algorithm
{
private:
	Block* algorithm;
	Operator** operators;

	int operatorCount;
public:
	Algorithm(Operator** operators, Block* algorithm, int operatorCount);
	~Algorithm();

	float getNextSample();
	Operator** getOperators();
};

