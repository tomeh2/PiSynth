#pragma once

#include "WaveGenerator.h"
#include "EnvelopeGenerator.h"
#include "Block.h"

/**
Smallest unit capable which is capable of producing relatively complex sound and
is able to interact with other operators.
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
	void addEnvelopePhase(int expCoeff, float targetVal, int holdTime);
	void trigger();
	void release();
	bool isActive();
};

