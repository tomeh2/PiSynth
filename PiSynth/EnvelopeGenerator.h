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
	std::vector<float> sustainTimes;
	std::vector<float> targetVals;
	std::vector<float> transitionVals;

	int currentState = 0;
	float currVal = 0.f;	//Holds the current value of the signal
	float deltaTime = 0.f;
	float time = 0.f;
	float translation = 0.f;	//Values of inverse functions

	void updateTime();
	void incrementState();
	void calculateTranslation();
	float calculateNextValue();

	void addNewStateP(float expCoeff, float targetVal, float holdTime);
public:
	EnvelopeGenerator(int sampleRate);
	~EnvelopeGenerator();

	/*
	Calculates and returns the next value of the envelope (updates the time as well)
	*/
	float getNextValue();

	/*
	Adds a new state to the envelope. Each state is one phase of the envelope.
	For example the ADSR envelope has 4 stages: A, D, S and R;

	@param expCoeff -> determines the speed of the given state. Negative values for falling envelope
	@param transitionVal -> value at which the envelope goes to a new state and ends this one
	@param sustainHold -> how long a sustain level will be held. If given 0 it will leave the state when release is called.
						  If the EG is not in sustain state this value is ignored.
	*/
	void addNewState(int speed, float targetVal, int holdTime);

	/*
	Puts the envelope into the first phase which should be attack (considering that the EG was properly programmed)
	*/
	void trigger();

	/*
	Puts the envelope generator into the last phase which sould be release (considering that the EG was properly programmed)
	*/
	void release();

	/*
	Returns FALSE if the EG is currently idle, that is to say that the currentState variable of the EG has the value of 0
	*/
	bool isActive();
};