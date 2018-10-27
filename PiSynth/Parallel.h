#pragma once

#include "Block.h"

#include <vector>

class Parallel
{
private:
	std::vector<Block*>* elements;
public:
	Parallel();
	~Parallel();

	void addBlock(Block* block);
	float getNextSample(float input);
};

