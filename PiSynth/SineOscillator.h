#pragma once

#include "Oscillator.h"

class SineOscillator : public Oscillator
{
public:
	SineOscillator(int, float);
	~SineOscillator();
	
	float process();
};