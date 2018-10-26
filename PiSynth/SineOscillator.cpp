#include "SineOscillator.h"

SineOscillator::SineOscillator(int sampleRate, float frequency)
{
	this->sampleRate = sampleRate;
	this->setFrequency(frequency);
}

SineOscillator::~SineOscillator()
{
}

float SineOscillator::process()
{
	float sample = sin(this->time);
	this->update();
	return sample;
}