#include "Operator.h"

Operator::Operator(int sampleRate)
{
	this->waveGenerator = new WaveGenerator(sampleRate);
	this->envelopeGenerator = new EnvelopeGenerator(sampleRate);
	/*
	this->envelopeGenerator->addNewState(0.005f, 1.f, 0.f);
	//this->envelopeGenerator->addNewState(0.f, 1.f, 0.1f);
	this->envelopeGenerator->addNewState(-0.01f, 0.65f, 0.f);
	this->envelopeGenerator->addNewState(-1.0f, 0.f, 0.f);
	this->envelopeGenerator->addNewState(-0.1f, 0.f, 0.f);*/
}

Operator::~Operator()
{
	delete this->waveGenerator;
	delete this->envelopeGenerator;
}

float Operator::getNextSample(float input)
{
	return this->waveGenerator->getNextSample(input) * this->envelopeGenerator->getNextValue();
}

void Operator::setWaveform(Waveform waveform)
{
	this->waveGenerator->setOscillatorType(waveform);
}

void Operator::setOutputLevel(float outLevel)
{
	this->outputLevel = outLevel;
}

void Operator::setModulationSensitivity(float newModSens)
{
	this->waveGenerator->setModulationSensitivity(newModSens);
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
	this->envelopeGenerator->addNewState(expCoeff, targetVal, holdTime);
}

void Operator::trigger()
{
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