#pragma once

#include "Block.h"

class Feedback : public Block
{
private:
	Block* block = nullptr;

	float lastVal;
public:
	Feedback();
	~Feedback();

	/**
	The block which will have its output fed back into the input.
	The sample which gets passed as input happened at time T - 1.
	(It is the last sample that was calculated, not this new one)
	This function will only have an effect when called for the first time.

	@param block -> pointer to the block to be added
	@returns -> NOTHING
	*/
	void setBlock(Block* block);

	/**
	This function calculates and returns the next sample of the signal.
	IMPORTANT: Feedback does NOT use the input variable. Any value
	passed will just be ignored.

	@param input -> NOT USED!
	@returns -> next sample of the signal
	*/
	float getNextSample(float input);
};

