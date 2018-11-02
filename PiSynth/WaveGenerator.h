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

	/**
	Calculates and returns the next sample of the signal.

	@param input -> input into this wave generator (will do phase modulation)
	@returns -> next sample of the signal
	*/
	float getNextSample(float input);

	/**
	Sets the waveform that this wave generator generates to the one specified by the argument.
	----------------------------
	Possible waveforms:
		- SINE_WAVE
		- SQUARE_WAVE

	@param waveform -> SINE_WAVE or SQUARE_WAVE
	*/
	void setOscillatorType(Waveform waveform);

	/**
	Sets the frequency of the periodic waveform that this wave generator generates
	to the value specified in the argument.

	@param newFrequency
*/
	void setFrequency(float newFrequency);
	float getFrequency();

	/**
	Sets the detune frequency of the waveform to the value specified in the argument.
	The detune frequency gets added to the base frequency, so basically it only modifies 
	the base frequency. The resulting frequency of the wave generator will be
	----------------
	resultingFreq = baseFrequency + detuneFrequency
	----------------
	@param newDetuneFrequency
	*/
	void setDetuneFrequency(float newDetuneFrequency);
	float getDetuneFrequency();
};

