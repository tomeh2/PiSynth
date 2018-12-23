#pragma once

#include <vector>

//THIS IS THE ENVELOPE GENERATOR

class EnvelopeMemory
{
private:
	std::vector<float> samples;
	std::vector<int> isStateSustain;

	int timer = 0;
public:
	EnvelopeMemory();
	~EnvelopeMemory();


};

