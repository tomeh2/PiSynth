#pragma once

#include "Channel.h"
#include "Patch.h"

#include <vector>

/*
Renderer is a class which provides control over individual channels.
It allows for things like multi-timbrality, some effects etc.

It also provides multi-threading for individual channels to increase
speed of execution.
*/

class Renderer
{
private:
	std::vector<Channel*> channels;

	int numChannels;
public:
	Renderer(int sampleRate, int numChannels, int polyphonyPerChannel, Patch patch);
	~Renderer();

	/*
	Calculates and returns the next sample.

	@return -> next sample of the signal
	*/
	float getNextSample();

	/*
	Takes a midi command and executes it.

	@param - TODO
	*/
	void processCommand(int type, int channel, int keyNum);
	void setPatch(int channel, Patch patch);
};

