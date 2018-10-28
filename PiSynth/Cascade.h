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

	/**
	Adds a new element to the cascade. The element is inserted at the beginning of the vector.

	@param block -> pointer to the block to be added
	@returns -> NOTHING
	*/
	void addBlock(Block* block);

	/**
	This function returns the sample of the last element connected in the cascade.
	The input gets passed to the "top" element in the vector. This makes it behave
	like all elements are connected in a series.

	@param input -> gets passed to the "top" element of the cascade
	@returns -> the next sample of the signal
	*/
	float getNextSample(float input);
};

