#include "SineOscillator.h"
#include "Clock.h"
#include "FastMath.h"

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
	float sample = sin(fmod(Clock::getClockSignal() * (TWO_PI * this->frequency / sampleRate), TWO_PI) + input);
	this->update();
	return sample;
}