#include "Operator.h"

Operator::Operator(int sampleRate)
{
	this->waveGenerator = new WaveGenerator(sampleRate);
}

Operator::~Operator()
{
	delete this->waveGenerator;
}

float Operator::getNextSample(float input)
{
	return this->waveGenerator->getNextSample(input);
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