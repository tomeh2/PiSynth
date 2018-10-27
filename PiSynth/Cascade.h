#pragma once

#include "Block.h"

#include <vector>

class Cascade : public Block
{
private:
	std::vector<Block*>* elements;
public:
	Cascade();
	~Cascade();

	void addBlock(Block* block);
	float getNextSample(float input);
};

