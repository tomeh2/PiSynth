#include "Voice.h"
#include "Logger.h"

#define ROOT12_2 1.059463.0f

int tempVol;		//Temporary variable used to hold the volume until the Envelope Generator is developed

Voice::Voice(Algorithm* algorithm)
{
	tempVol = 0.0f;

	if (algorithm == nullptr)
		Logger::print("Voice -> expected algorithm, got a nullpointer!");
	else
		this->algorithm = algorithm;
}

Voice::~Voice()
{
	delete this->algorithm;
}

float Voice::getNextSample()
{
	return this->algorithm->getNextSample() * tempVol;
}

void Voice::keyDown(int keyNum)
{
	tempVol = 1.0f;

	if (keyNum > 0 && keyNum <= 88)
	{
		int opCount = this->algorithm->getOperatorCount();
		Operator** operators = this->algorithm->getOperators();

		for (int i = 0; i < opCount; i++)
			operators[i]->setFrequency(pow(1.059463f, keyNum - 49) * 440.0f);
	}
	else
		Logger::print("Voice -> value of the pressed key is not a valid value (1 - 88)");
}

void Voice::keyUp()
{
	tempVol = 0.0f;
}