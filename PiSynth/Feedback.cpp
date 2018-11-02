#include "Feedback.h"
#include "Logger.h"

Feedback::Feedback()
{
	this->lastVal = 0.0f;
}

Feedback::~Feedback()
{
	delete this->block;
}

void Feedback::setBlock(Block* block)
{
	if (this->block == nullptr)
		this->block = block;
	else
		Logger::print("Feedback -> Tried to set a null pointer as a block!");
}

float Feedback::getNextSample(float input)
{
	float sample = this->block->getNextSample(lastVal);
	this->lastVal = sample;
	return sample;
}