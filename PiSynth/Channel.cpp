#include "Channel.h"
#include "AlgorithmGenerator.h"
#include "Logger.h"

#define SWEEP_PERIOD 4000

Channel::Channel(int sampleRate, int maxPolyphony, Patch patch)
{
	this->maxPolyphony = maxPolyphony;
	/*
	for (int i = 0; i < this->maxPolyphony; i++)
	{
		this->voices.push_back(new Voice(AlgorithmGenerator::generateAlgorithmFromString(sampleRate, patch.getAlgDescription(), patch.getOperatorCount())));
		this->freeVoices.push(this->voices[i]);
	}*/

	this->setNewPatch(patch);

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

void Channel::setNewPatch(Patch patch)
{	
	//DELETE ALL EXISTING VOICES
	if (this->voices.size() != 0)
	{
		for (int i = 0; i < this->maxPolyphony; i++)
			delete this->voices[i];

		this->voices.clear();
		this->activeVoices.clear();
		this->freeVoices = {};
	}

	//CREATE NEW VOICES
	for (int i = 0; i < this->maxPolyphony; i++)
	{
		this->voices.push_back(new Voice(AlgorithmGenerator::generateAlgorithmFromString(44100, patch.getAlgDescription(), patch.getOperatorCount())));
		this->freeVoices.push(this->voices[i]);
	}

	//INITIALIZE NEWLY CREATED VOICES
	Operator** operators;
	for (int i = 0; i < this->maxPolyphony; i++)
	{
		operators = this->voices[i]->getOperators();
		for (int j = 0; j < patch.getOperatorCount(); j++)
		{
			operators[j]->setFrequencyRatio(patch.getFreqRatio(j));
			operators[j]->setOutputLevel(patch.getOutputLevel(j));
			operators[j]->setModulationSensitivity(patch.getModulationSensitivity(j));

			for (int k = 0; k < patch.getEnvSegmentCount(); k++)
				operators[j]->addEnvelopePhase(patch.getCoefficients(j)[k], patch.getTargets(j)[k], patch.getHoldTimes(j)[k]);
		}
	}
}