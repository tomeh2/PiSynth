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

	/**
	Adds a new element to the parallel. The element is inserted at the beginning of the vector.

	@param block -> pointer to the block to be added
	@returns -> NOTHING
	*/
	void addBlock(Block* block);

	/**
	This function returns a sum of all results calculated by the elements it contains
	which makes it behave like the elements are connected in a parallel.

	@param input -> gets passed to ALL elements that make up the system
	@returns -> nest sample of the signal
	*/
	float getNextSample(float input);
};

