#include "Parallel.h"
#include "Logger.h"

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
	if (block == nullptr)
		Logger::print("Parallel -> Tried to pass a null pointer as a block when adding an element!");
	else
		this->elements->insert(this->elements->begin(), block);
}

float Parallel::getNextSample(float input)
{
	float temp = 0.0f;

	for (Block* element : *this->elements)
		temp += element->getNextSample(input);

	return temp;
}
