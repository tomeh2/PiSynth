#include "Channel.h"
#include "AlgorithmGenerator.h"
#include "Logger.h"

#define SWEEP_PERIOD 4000

Channel::Channel(int sampleRate, int maxPolyphony)
{
	this->maxPolyphony = maxPolyphony;

	for (int i = 0; i < this->maxPolyphony; i++)
	{
		this->voices.push_back(new Voice(AlgorithmGenerator::generateAlgorithmFromString(sampleRate, "p(c(1,f(2)),c(3,f(4)))", 4)));
		this->freeVoices.push(this->voices[i]);
	}
	Logger::print(std::string("Channel initialization completed | Max Polyphony = " + std::to_string(this->maxPolyphony) + " Voices").c_str());
}

Channel::~Channel()
{
	for (int i = 0; i < this->maxPolyphony; i++)
		delete this->voices[i];
}

void Channel::performSweep()
{
	for (auto it = this->activeVoices.begin(); it != this->activeVoices.end(); it++)
	{	
		if (!it->second->isActive())
		{
			Voice* v = it->second;
			this->freeVoices.push(v);
			this->activeVoices.erase(it);
		}
	}
}

float Channel::getNextSample()
{
	float sample = 0.0f;
	for (auto it = this->activeVoices.begin(); it != this->activeVoices.end(); it++)
	{
		Voice* v = it->second;
		sample += v->getNextSample();
	}
	this->sweepCounter++;
	
	if (this->sweepCounter == SWEEP_PERIOD)
	{
		this->sweepCounter = 0;
		this->performSweep();
	}
	return sample;
}

void Channel::keyDown(int keyNum)
{
	if (keyNum > 0 && keyNum <= 127)
	{
		if (!this->freeVoices.empty() && this->activeVoices.count(keyNum) == 0)
		{
			Voice* v = this->freeVoices.top();
			this->freeVoices.pop();

			v->keyDown(keyNum);

			this->activeVoices[keyNum] = v;
		}

		if (this->activeVoices.count(keyNum) == 1)
		{
			this->activeVoices[keyNum]->keyDown(keyNum);
		}
	}

}

void Channel::keyUp(int keyNum)
{
	if (keyNum > 0 && keyNum <= 127)
		try
		{
			this->activeVoices.at(keyNum)->keyUp();
		}
		catch (std::out_of_range e)
		{
		//	Logger::print("Tried to deactivate a voice that was not active in the first place!");
		}
}
