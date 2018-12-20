#include "EnvelopeGenerator.h"

#include <math.h>

#define EXP_CONST 1.2f

EnvelopeGenerator::EnvelopeGenerator()
{
}

EnvelopeGenerator::~EnvelopeGenerator()
{
}

void EnvelopeGenerator::updateTime()
{
	this->time += (1.f / 44100.f);
}

#include "Logger.h"
void EnvelopeGenerator::calculateTranslation()
{
	if (this->currentState != this->expCoeffs.size())
	{
		float coeff = this->expCoeffs[this->currentState];
		if (coeff > 0.f)
		{
			this->translation = coeff * log(1.f - this->currVal / EXP_CONST);
		}
		else if (coeff < 0.f)
		{
			this->translation = coeff * log(this->currVal - this->transitionVals[this->currentState]);
			coeff = 0.f;
		}
	}
}

float EnvelopeGenerator::calculateNextValue()
{
	if (currentState != 0)
	{
		if (this->expCoeffs[this->currentState - 1] > 0.f)
		{
			this->currVal = EXP_CONST * (1.f - 
				exp((-this->time + this->translation) / this->expCoeffs[this->currentState - 1]));

			if (this->currVal >= this->transitionVals[this->currentState - 1] * 0.99f)
			{
				this->currVal = this->transitionVals[this->currentState - 1];
				this->time = 0.f;
				this->calculateTranslation();
				this->currentState++;
			}
		}
		else if (this->expCoeffs[this->currentState - 1] < 0.f)
		{
			this->currVal = exp((-this->time - translation) / abs(this->expCoeffs[this->currentState - 1]))
				+ this->transitionVals[currentState - 1];

			if (this->currVal <= 0.001f)
			{
				this->currVal = this->transitionVals[this->currentState - 1];
				this->time = 0.f;
				this->calculateTranslation();
				this->currentState++;
			}
		}

		if (this->currentState == this->expCoeffs.size() + 1)
			this->currentState = 0;
	}
	return this->currVal;
}

float EnvelopeGenerator::getNextValue()
{
	if (this->currentState != 0)
	{
		float val = this->calculateNextValue();
		this->updateTime();
		return val;
	}
	else
	{
		return 0.f;
	}
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
	if (this->isActive())
		this->currentState = this->expCoeffs.size();
}

bool EnvelopeGenerator::isActive()
{
	return this->currentState != 0;
}