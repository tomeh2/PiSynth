#include "Channel.h"
#include "AlgorithmGenerator.h"
#include "Logger.h"

Channel::Channel(int sampleRate, int maxPolyphony)
{
	this->maxPolyphony = maxPolyphony;

	for (int i = 0; i < this->maxPolyphony; i++)
	{
		this->voices.push_back(new Voice(AlgorithmGenerator::generateAlgorithmFromString(sampleRate, "p(c(1,f(2)),c(3,f(4)))", 4)));
		this->freeVoices.push(this->voices[i]);
	}

	Logger::print(std::string("Active voices: " + std::to_string(this->activeVoices.size())).c_str());
	Logger::print(std::string("Channel initialization completed | Max Polyphony = " + std::to_string(this->maxPolyphony) + " Voices").c_str());
}

Channel::~Channel()
{
	for (int i = 0; i < this->maxPolyphony; i++)
		delete this->voices[i];
}

float Channel::getNextSample()
{
	float sample = 0.0f;
	for (auto it = this->activeVoices.begin(); it != this->activeVoices.end(); it++)
	{
		Voice* v = it->second;
		sample += v->getNextSample();
	}
	return sample;
}

void Channel::keyDown(int keyNum)
{
	if (keyNum > 0 && keyNum <= 127)
		if (!this->freeVoices.empty())
		{
			Voice* v = this->freeVoices.top();
			this->freeVoices.pop();

			v->keyDown(keyNum);

			this->activeVoices[keyNum] = v;
		}
		else
			Logger::print("Can't activate a new voice. No free voices are left!");
}

void Channel::keyUp(int keyNum)
{
	if (keyNum > 0 && keyNum <= 127)
		try
		{
			Voice* v = this->activeVoices.at(keyNum);
			v->keyUp();
			this->activeVoices.erase(keyNum);
			this->freeVoices.push(v);
		}
		catch (std::out_of_range e)
		{
			Logger::print("Tried to deactivate a voice that was not active in the first place!");
		}
}
