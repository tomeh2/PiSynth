#include "Operator.h"

Operator::Operator(int sampleRate)
{
	this->waveGenerator = new WaveGenerator(sampleRate);

	this->envelopeGenerator.addNewState(0.07f, 1.0f);
	this->envelopeGenerator.addNewState(-1.02f, 0.0f);
}

Operator::~Operator()
{
	delete this->waveGenerator;
}
/*
float Operator::getNextSample(float input)
{
	return this->waveGenerator->getNextSample(input);
}*/
float Operator::getNextSample(float input)
{
	return this->waveGenerator->getNextSample(input) * this->envelopeGenerator.getNextValue();
}

void Operator::setWaveform(Waveform waveform)
{
	this->waveGenerator->setOscillatorType(waveform);
}

void Operator::setFrequency(float newFrequency)
{
	this->waveGenerator->setFrequency(newFrequency);
}

void Operator::setDetuneFrequency(float newDetuneFrequency)
{
	this->waveGenerator->setDetuneFrequency(newDetuneFrequency);
}

void Operator::trigger()
{
	this->envelopeGenerator.trigger();
}

void Operator::release()
{
	this->envelopeGenerator.release();
}