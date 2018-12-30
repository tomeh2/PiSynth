#pragma once

#include "WaveGenerator.h"
#include "EnvelopeGenerator.h"
#include "Block.h"

/**
Operator in this synthesizer is used a bit differently then in an ordinary FM synth.
While they do perform the same exact function, in this synthesizer the Operator is
used in the "Signal generation" phase of sound synthesis. ---DESCRIPTION NOT DONE!!!!
*/

class Operator : public Block
{
private:
	EnvelopeGenerator* envelopeGenerator;
	WaveGenerator* waveGenerator;

	float baseFrequency = 0.f;
	float frequencyRatio = 1.f;
	float outputLevel = 1.f;
public:
	Operator(int sampleRate);
	~Operator();

	float getNextSample(float input);
	void setWaveform(Waveform waveform);
	void setOutputLevel(float outLevel);
	void setModulationSensitivity(float newModSens);
	void setFrequencyRatio(float newRatio);
	void setFrequency(float newFrequency);
	void setDetuneFrequency(float newDetuneFrequency);
	void addEnvelopePhase(float expCoeff, float targetVal, float holdTime);
	void trigger();
	void release();
	bool isActive();
};

