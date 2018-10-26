#include "SquareOscillator.h"

SquareOscillator::SquareOscillator(int sampleRate, float frequency)
{
	this->sampleRate = sampleRate;
	this->setFrequency(frequency);
}

SquareOscillator::~SquareOscillator()
{
}

float SquareOscillator::process()
{
	float sample = sgn(sin(this->time));
	this->update();
	return sample;
}