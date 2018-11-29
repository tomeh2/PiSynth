#pragma once

#include "Voice.h"

#include <stack>
#include <map>

class Channel
{
private:
	int maxPolyphony;

	Voice** voices;
	std::stack<Voice*> freeVoices;
	std::map<int, Voice*> activeVoices;
public:
	Channel(int sampleRate, int maxPolyphony);
	~Channel();

	float getNextSample();
	void keyDown(int keyNum);
	void keyUp(int keyUp);
};

