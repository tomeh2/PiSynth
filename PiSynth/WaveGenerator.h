#pragma once

#include "SineOscillator.h"
#include "SquareOscillator.h"

/**
WaveGenerator class provides a simpler way to handle large amounts of oscillators.
It also provides a way to easily add new types of oscillators.
*/

enum Waveform
{
	SINE_WAVE,
	SQUARE_WAVE
};

class WaveGenerator
{
private:
	int sampleRate;

	Oscillator* oscillator = nullptr;
public:
	WaveGenerator(int sampleRate);
	~WaveGenerator();

	float getNextSample(float input);
	void setOscillatorType(Waveform waveform);
	void setFrequency(float newFrequency);
	void setDetuneFrequency(float newDetuneFrequency);
};

