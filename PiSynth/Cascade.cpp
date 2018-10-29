#include "Cascade.h"
#include "Logger.h"

#include <iostream>

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
	std::cout << "Temp: " << block << "\n";

	if (block == nullptr)
		Logger::print("Cascade -> Tried to pass a null pointer as a block when adding an element!");
	else
		this->elements->insert(this->elements->begin(), block);
}

float Cascade::getNextSample(float input)
{
	float temp = input;

	std::cout << "Size: " << this->elements->size() << "\n"; 

	for (Block* element : *this->elements)
		temp = element->getNextSample(temp);

	return temp;
}