#include "Voice.h"
#include "Logger.h"
#include "Clock.h"

#include <string>

#define ROOT12_2 1.059463.0f

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

	if (keyNum > 0 && keyNum <= 127)
	{
		int opCount = this->algorithm->getOperatorCount();
		Operator** operators = this->algorithm->getOperators();

		for (int i = 0; i < opCount; i++)
			operators[i]->setFrequency(pow(1.059463f, keyNum - 69) * 440.0f);
	}
	else
		Logger::print("Voice -> value of the pressed key is not a valid value (1 - 127)");
}

void Voice::keyUp()
{
	tempVol = 0.0f;
}

bool Voice::isActive()
{
	return tempVol == 1.0f;
}