#pragma once

#include "Oscillator.h"

class SineOscillator : public Oscillator
{
public:
	SineOscillator(int sampleRate, float frequency);
	~SineOscillator();
	
	float process(float input);
};