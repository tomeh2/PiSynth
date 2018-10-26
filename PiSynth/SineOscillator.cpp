#include "SineOscillator.h"

SineOscillator::SineOscillator(int sampleRate, float frequency)
{
	this->sampleRate = sampleRate;
	this->setFrequency(frequency);
}

SineOscillator::~SineOscillator()
{
}

float SineOscillator::process(float input)
{
	float sample = sin(this->time + input);
	this->update();
	return sample;
}