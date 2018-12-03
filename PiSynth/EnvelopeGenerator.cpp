#include "EnvelopeGenerator.h"

#include <math.h>

EnvelopeGenerator::EnvelopeGenerator()
{
}

EnvelopeGenerator::~EnvelopeGenerator()
{
}

void EnvelopeGenerator::updateTime()
{
	this->time += 0.001f;
}

float EnvelopeGenerator::calculateNextValue()
{
	if (currentState != 0)
	{
		float expCoeff = this->expCoeffs[this->currentState];
		if (expCoeff >= 0.f)
		{
			this->currVal += pow(expCoeff * this->time, expCoeff - 1.f);

			if (this->currVal >= this->transitionVals[this->currentState])
				this->currentState++;
		}
		else
		{
			this->currVal -= pow(expCoeff * this->time, expCoeff - 1.f);

			if (this->currVal <= this->transitionVals[this->currentState])
				this->currentState++;
		}

		if (this->currVal <= 0.0001f)
		{
			this->currentState = 0;
			this->currVal = 0.f;
		}
	}
	return this->currVal;
}

void EnvelopeGenerator::addNewState(float expCoeff, float transitionVal)
{
	this->expCoeffs.push_back(expCoeff);
	this->transitionVals.push_back(transitionVal);
}

void EnvelopeGenerator::trigger()
{
	this->currentState = 1;
}

void EnvelopeGenerator::release()
{
	this->expCoeffs.size() - 1;
}