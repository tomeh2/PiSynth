#pragma once

#include <vector>

/*
This class defines an Envelope Generator. Envelope Generator generates envelope
signals for use in operators and filters. 

If currentState is equal to 0 that is the inactive state of the envelope

CAPABILITIES:
	- Multi-phase envelope generation (more detailed explanation in doc.)
	- Linear and exponential functions
*/

class EnvelopeGenerator
{
private:
	std::vector<float> expCoeffs;		//Coefficient which determines the "speed" of it's phase
	std::vector<float> transitionVals;

	int currentState = 0;
	float currVal = 0.f;	//Holds the current value of the signal
	float time = 0.f;

	void updateTime();
	float calculateNextValue();
public:
	EnvelopeGenerator();
	~EnvelopeGenerator();

	/*
	Adds a new state to the envelope. Each state is one phase of the envelope.
	For example the ADSR envelope has 4 stages: A, D, S and R;

	@param expCoeff -> determines the speed of the given state. Negative values for falling envelope
	@param transitionVal -> value at which the envelope goes to a new state and ends this one
	*/
	void addNewState(float expCoeff, float transitionVal);
	float getNextValue();
	void trigger();
	void release();
};

