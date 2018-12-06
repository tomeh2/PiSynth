#include "EnvelopeGenerator.h"
#include "Logger.h"

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
	this->time += 0.001f;
}

float EnvelopeGenerator::calculateNextValue()
{
	
	if (currentState != 0)
	{
		if (this->expCoeffs[this->currentState - 1] >= 0.f)
		{
			Logger::print(std::to_string(this->expCoeffs[this->currentState - 1]).c_str());

			float expo = -1.f / (this->time);
			this->currVal = pow(M_E, expo);

			if (this->currVal >= 0.99f * this->transitionVals[this->currentState - 1])
			{
				Logger::print(std::to_string(this->currentState).c_str());
				this->currVal = this->transitionVals[this->currentState - 1];
				this->time = 0.f;
				this->currentState++;
			}
		}
		else
		{
			this->currVal = pow(M_E, (-this->time) / 1.f);

			

			if (this->currVal <= 0.01f * this->transitionVals[this->currentState - 1])
			{
				this->currVal = this->transitionVals[this->currentState - 1];
				this->time = 0.f;
				this->currentState++;
			}
		}
		this->updateTime();

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
	this->expCoeffs.size() - 1;
}