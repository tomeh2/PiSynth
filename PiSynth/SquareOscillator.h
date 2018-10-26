#pragma once

#include "Oscillator.h"

class SquareOscillator : public Oscillator
{
private:		//Contains sgn function for now. Will probably be implemented in a separate math class in the future 
	float sgn(float val)
	{
		if (val < 0.0f)
			return -1.0f;
		else if (val > 0.0f)
			return 1.0f;
		else
			return 0.0f;
	}

public:
	SquareOscillator(int sampleRate, float frequency);
	~SquareOscillator();

	float process(float input);
};

