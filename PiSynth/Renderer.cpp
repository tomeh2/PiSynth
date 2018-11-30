#include "Renderer.h"
#include "Channel.h"
#include "Logger.h"

Renderer::Renderer(int sampleRate, int numChannels, int polyphonyPerChannel)
{
	this->numChannels = numChannels;

	Logger::print(std::string("Creating a renderer. NUM CHANNELS = " + std::to_string(numChannels) + " | PPC = " + std::to_string(polyphonyPerChannel)).c_str());

	for (int i = 0; i < numChannels; i++)
	{
		this->channels.push_back(new Channel(sampleRate, polyphonyPerChannel));
		Logger::print(std::string("Initializing channel " + std::to_string(i)).c_str());
	}
}

Renderer::~Renderer()
{
	for (int i = 0; i < this->numChannels; i++)
		delete this->channels[i];
}

float Renderer::getNextSample()
{
	float sample = 0.f;

	for (int i = 0; i < numChannels; i++)
		sample += this->channels[i]->getNextSample();

	return sample;
}

void Renderer::processCommand(int type, int channel, int keyNum)
{
	switch (type)
	{
	case 0x90:
		this->channels[channel]->keyDown(keyNum);
		Logger::print(std::string("Command: 0x80 | Channel: " + std::to_string(channel) + " | KeyNum: " + std::to_string(keyNum)).c_str());
		break;
	case 0x80:
		this->channels[channel]->keyUp(keyNum);
		Logger::print(std::string("Command: 0x90 | Channel: " + std::to_string(channel) + " | KeyNum: " + std::to_string(keyNum)).c_str());
		break;
	}
}