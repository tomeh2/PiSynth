#include "Operator.h"

Operator::Operator(int sampleRate)
{
	this->waveGenerator = new WaveGenerator(sampleRate);
	this->envelopeGenerator = new EnvelopeGenerator(sampleRate);
}

Operator::~Operator()
{
	delete this->waveGenerator;
	delete this->envelopeGenerator;
}

float Operator::getNextSample(float input)
{
	return this->waveGenerator->getNextSample(input) * this->envelopeGenerator->getNextValue() * this->outputLevel;
}

void Operator::setWaveform(Waveform waveform)
{
	this->waveGenerator->setOscillatorType(waveform);
}

void Operator::setOutputLevel(float outLevel)
{
	this->outputLevel = outLevel;
}

void Operator::setModulationSensitivityRange(float lowerLimit, float upperLimit)
{
	this->modSensLowerLimit = lowerLimit;
	this->modSensUpperLimit = upperLimit;
}

void Operator::setFrequencyRatio(float newRatio)
{
	this->frequencyRatio = newRatio;
	this->setFrequency(this->baseFrequency);
}

void Operator::setFrequency(float newFrequency)
{
	this->baseFrequency = newFrequency;
	this->waveGenerator->setFrequency(newFrequency * this->frequencyRatio);
}

void Operator::setDetuneFrequency(float newDetuneFrequency)
{
	this->waveGenerator->setDetuneFrequency(newDetuneFrequency);
}

void Operator::addEnvelopePhase(float expCoeff, float targetVal, float holdTime)
{
	this->envelopeGenerator->addNewStateP(expCoeff, targetVal, holdTime);
}

void Operator::trigger(int keyNum)
{
	float modSens = ((this->modSensUpperLimit - this->modSensLowerLimit) / 126) * (keyNum - 1) + this->modSensLowerLimit;

	this->waveGenerator->setModulationSensitivity(modSens);

	this->envelopeGenerator->trigger();
}

void Operator::release()
{
	this->envelopeGenerator->release();
}

bool Operator::isActive()
{
	return this->envelopeGenerator->isActive();
}