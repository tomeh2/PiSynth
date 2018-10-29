#pragma once

#include "Block.h"
#include "Operator.h"

class Algorithm
{
private:
	Block* algorithm;
	Operator* operators;
public:
	Algorithm();
	~Algorithm();
};

