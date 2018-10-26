#pragma once

#include <math.h>

#define PI 3.14159265358979f
#define TWO_PI 6.28318530717958f

/**
This is the base Oscillator class. Every oscillator should inherit this header.
It provides all variables (and constants) that are needed in order to make an oscillator 
and the only difference between oscillators should be in the implementation of the process function
which is where the actual signal generation happens.
*/
class Oscillator
{
protected:
	int sampleRate = 0;		
	float frequency = 0.0f;
	float detuneFrequency = 0.0f;

	float time = 0.0f;
	float timeStep = 0.0f;

	void update()
	{
		this->time += this->timeStep;

		if (this->time >= TWO_PI)
			this->time -= TWO_PI;
	}
public:
	virtual float process(float input) = 0;		//this is the function that implements the signal generation
	
	void setFrequency(float newFrequency)
	{
		this->frequency = newFrequency;

		this->timeStep = TWO_PI * this->frequency / this->sampleRate;
	}

	void setDetuneFrequency(float detuneFrequency)
	{
		this->setFrequency(this->frequency + detuneFrequency);
	}

	float getFrequency() { return this->frequency; }
	float getDetuneFrequency() { return this->detuneFrequency; }
};