#include "WaveGenerator.h"
#include "Logger.h"

WaveGenerator::WaveGenerator(int sampleRate)
{
	this->sampleRate = sampleRate;

	this->setOscillatorType(SINE_WAVE);
}

WaveGenerator::~WaveGenerator()
{
	delete this->oscillator;
}

/**
Calculates the next sample and returns it's value.
*/
float WaveGenerator::getNextSample(float input)
{
	this->oscillator->process(input);
}

void WaveGenerator::setOscillatorType(Waveform waveform)
{
	delete this->oscillator;

	switch (waveform)
	{
	case SINE_WAVE:
		this->oscillator = new SineOscillator(this->sampleRate, 440.0f);
		Logger::print("WaveGenerator -> Waveform changed to SINE_WAVE");
		break;
	case SQUARE_WAVE:
		this->oscillator = new SquareOscillator(this->sampleRate, 440.0f);
		Logger::print("WaveGenerator -> Waveform changed to SQUARE_WAVE");
		break;
	}
}

/**
Sets the frequency of the oscillator currently used by this Wave Generator.
*/
void WaveGenerator::setFrequency(float newFrequency)
{
	this->oscillator->setFrequency(newFrequency);
}

/**
Sets the detune frequency of the oscillator currently used by this Wave Generator.
*/
void WaveGenerator::setDetuneFrequency(float newDetuneFrequency)
{
	this->oscillator->setDetuneFrequency(newDetuneFrequency);
}

float WaveGenerator::getFrequency()
{
	return this->oscillator->getFrequency();
}

float WaveGenerator::getDetuneFrequency()
{
	return this->oscillator->getDetuneFrequency();
}