#include "Parallel.h"

Parallel::Parallel()
{
	this->elements = new std::vector<Block*>;
}

Parallel::~Parallel()
{
	delete this->elements;
}

void Parallel::addBlock(Block* block)
{
	this->elements->insert(this->elements->begin(), block);
}

float Parallel::getNextSample(float input)
{
	float temp = 0.0f;

	for (Block* element : *this->elements)
		temp += element->getNextSample(input);

	return temp;
}
