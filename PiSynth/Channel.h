#pragma once

#include "Voice.h"

#include <vector>
#include <stack>
#include <map>

class Channel
{
private:
	int maxPolyphony;
	int sweepCounter = 0;

	std::vector<Voice*> voices;
	std::stack<Voice*> freeVoices;
	std::map<int, Voice*> activeVoices;

	void performSweep();
public:
	Channel(int sampleRate, int maxPolyphony);
	~Channel();

	/*
	Calculates and returns the next sample
	*/
	float getNextSample(); 

	/*
	Activates a voice if there are free voices left.
	If there are no free voices left the message will be ignored.

	@param keyNum -> voice will be activated with this key
	*/
	void keyDown(int keyNum);

	/*
	Starts the release phase of the envelope.
	If there is no active voice with the given key number the message will be ignored.

	@param keyNum -> voice which will be released
	*/
	void keyUp(int keyNum);
};

