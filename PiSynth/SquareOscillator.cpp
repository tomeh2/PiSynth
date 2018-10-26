#include "SquareOscillator.h"

SquareOscillator::SquareOscillator(int sampleRate, float frequency)
{
	this->sampleRate = sampleRate;
	this->setFrequency(frequency);
}

SquareOscillator::~SquareOscillator()
{
}

float SquareOscillator::process(float input)
{
	float sample = sgn(sin(this->time + input));
	this->update();
	return sample;
}