#include "EnvelopeGenerator.h"

#include <math.h>

#define EXP_CONST 1.2f

EnvelopeGenerator::EnvelopeGenerator(int sampleRate)
{
	this->deltaTime = 1.f / sampleRate;
}

EnvelopeGenerator::~EnvelopeGenerator()
{
}

//----------------------------- PRIVATE FUNCTIONS ---------------------------------//

void EnvelopeGenerator::updateTime()
{
	this->time += this->deltaTime;
}

void EnvelopeGenerator::incrementState()
{
	this->currVal = this->transitionVals[this->currentState - 1];
	this->time = 0.f;
	this->calculateTranslation();
	this->currentState++;
}

void EnvelopeGenerator::calculateTranslation()
{
	if (this->currentState != this->expCoeffs.size())
	{
		float coeff = this->expCoeffs[this->currentState];
		if (coeff > 0.f)
			this->translation = coeff * log(1.f - this->currVal / EXP_CONST);
		else if (coeff < 0.f)
			this->translation = coeff * log(this->currVal - this->targetVals[this->currentState]);
		coeff = 0.f;
	}
}

float EnvelopeGenerator::calculateNextValue()
{
	int index = this->currentState - 1;

	if (this->expCoeffs[index] > 0.f)		//ENVELOPE GROWS IN THE CURRENT PHASE
	{
		this->currVal = EXP_CONST * (1.f - 
			exp((-this->time + this->translation) / this->expCoeffs[index]));

		if (this->currVal >= this->transitionVals[index])
			this->incrementState();
	}
	else if (this->expCoeffs[index] < 0.f)		//ENVELOPE FALLS IN THE CURRENT PHASE
	{
		this->currVal = exp((this->time + translation) / this->expCoeffs[index])
			+ this->targetVals[index];

		if (this->currVal <= this->transitionVals[index])
			this->incrementState();
	}
	else if (this->expCoeffs[index] == 0.f)	//ENVELOPE IS SUSTAINING
	{
		this->currVal = this->targetVals[index];

		if (this->time >= this->sustainTimes[index] && this->sustainTimes[index] != 0.f)
			this->incrementState();
	}

		if (this->currentState == this->expCoeffs.size() + 1)
			this->currentState = 0;
	return this->currVal;
}

//------------------------------- PUBLIC FUNCTIONS ------------------------------//

float EnvelopeGenerator::getNextValue()
{
	float val;

	if (this->currentState != 0)
	{
		val = this->calculateNextValue();
		this->updateTime();
	}
	else
		val = 0.f;

	return val;
}

void EnvelopeGenerator::addNewState(float expCoeff, float targetVal, float holdTime)
{
	this->expCoeffs.push_back(expCoeff);
	this->targetVals.push_back(targetVal);
	this->sustainTimes.push_back(holdTime);

	if (expCoeff > 0.f)
		this->transitionVals.push_back(targetVal * 0.999f);
	else if (expCoeff < 0.f)
		this->transitionVals.push_back(targetVal + targetVal * 0.001f);
	else
		this->transitionVals.push_back(targetVal);
}

void EnvelopeGenerator::trigger()
{
	if (this->isActive())
	{
		this->currentState = 0;
		this->calculateTranslation();
		this->time = 0.f;
	}
	else
		this->translation = 0.f;

	this->currentState = 1;
}

void EnvelopeGenerator::release()
{
	if (this->isActive())
	{
		this->currentState = this->expCoeffs.size() - 1;
		this->calculateTranslation();
		this->currentState++;
		this->time = 0.f;
	}
}

bool EnvelopeGenerator::isActive()
{
	return this->currentState != 0;
}