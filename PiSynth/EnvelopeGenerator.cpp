#include "EnvelopeGenerator.h"

#include <math.h>

EnvelopeGenerator::EnvelopeGenerator()
{
	this->expCoeffs.push_back(0.f);
	this->transitionVals.push_back(0.f);
}

EnvelopeGenerator::~EnvelopeGenerator()
{
}

void EnvelopeGenerator::updateTime()
{
	this->time += 0.1f;
}

float EnvelopeGenerator::calculateNextValue()
{
	if (currentState != 0)
	{
		float expCoeff = this->expCoeffs[this->currentState];
		if (expCoeff >= 0.f)
		{
			this->currVal += expCoeff * pow(this->time, expCoeff - 1.f) / 100.f;

			if (this->currVal >= this->transitionVals[this->currentState])
			{
				this->currVal = this->transitionVals[this->currentState];
				if (this->currentState != this->expCoeffs.size() - 1)
				{
					this->currentState++;
					this->time = 1.f;
				}
				else
				{
					this->currentState = 0;
					this->time = 0.f;
				}
			}
		}
		else
		{
			this->currVal += expCoeff * pow(this->time, expCoeff - 1.f) / 2.f;
			 
			if (this->currVal <= this->transitionVals[this->currentState])
			{
				this->currVal = this->transitionVals[this->currentState];
				if (this->currentState != this->expCoeffs.size() - 1)
				{
					this->currentState++;
					this->time = 0.f;
				}
				else
				{
					this->currentState = 0;
					this->time = 0.f;
				}
			}
		}
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
	this->expCoeffs.size() - 1;
}