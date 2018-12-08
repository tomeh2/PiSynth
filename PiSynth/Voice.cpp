#include "Voice.h"
#include "Logger.h"
#include "Clock.h"

#include <string>

#define ROOT12_2 1.059463.0f

Voice::Voice(Algorithm* algorithm)
{
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
	return this->algorithm->getNextSample();
}

void Voice::keyDown(int keyNum)
{
	if (keyNum > 0 && keyNum <= 127)
	{
		int opCount = this->algorithm->getOperatorCount();
		Operator** operators = this->algorithm->getOperators();

		for (int i = 0; i < opCount; i++)
		{
			operators[i]->setFrequency(pow(1.059463f, keyNum - 69) * 440.0f);
			operators[i]->trigger();
		}
	}
	else
		Logger::print("Voice -> value of the pressed key is not a valid value (1 - 127)");
}

void Voice::keyUp()
{
	for (int i = 0; i < this->algorithm->getOperatorCount(); i++)
		this->algorithm->getOperators()[i]->release();
}

bool Voice::isActive()
{
	bool isActive = false;

	for (int i = 0; i < this->algorithm->getOperatorCount(); i++)
		isActive |= this->algorithm->getOperators()[i]->isActive();

	return isActive;
}