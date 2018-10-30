#include "Cascade.h"
#include "Logger.h"

Cascade::Cascade()
{
	this->elements = new std::vector<Block*>;
}

Cascade::~Cascade()
{
	delete this->elements;
}

void Cascade::addBlock(Block* block)
{
	if (block == nullptr)
		Logger::print("Cascade -> Tried to pass a null pointer as a block when adding an element!");
	else
		this->elements->insert(this->elements->begin(), block);
}

float Cascade::getNextSample(float input)
{
	float temp = input;

	for (Block* element : *this->elements)
		temp = element->getNextSample(temp);

	return temp;
}