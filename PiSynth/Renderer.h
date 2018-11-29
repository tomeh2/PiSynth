#pragma once

#include "Channel.h"

#include <vector>

class Renderer
{
private:
	std::vector<Channel*> channels;

	int numChannels;
public:
	Renderer(int sampleRate, int numChannels, int polyphonyPerChannel);
	~Renderer();

	float getNextSample();
	void processCommand(int type, int channel, int keyNum);
};

