#pragma once

#include "WaveGenerator.h"
#include "Block.h"

/**
Operator in this synthesizer is used a bit differently then in an ordinary FM synth.
While they do perform the same exact function, in this synthesizer the Operator is
used in the "Signal generation" phase of sound synthesis. ---DESCRIPTION NOT DONE!!!!
*/

class Operator : public Block
{
private:
	WaveGenerator* waveGenerator;
public:
	Operator(int sampleRate);
	~Operator();

	float getNextSample(float input);
	void setWaveform(Waveform waveform);
	void setFrequency(float newFrequency);
	void setDetuneFrequency(float newDetuneFrequency);
};

