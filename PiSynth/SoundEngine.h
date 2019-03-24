#pragma once

#include "Renderer.h"

class SoundEngine
{
private:
	Renderer* audioRenderer;
public:
	SoundEngine(int sampleRate, int numChannels, int ppc, std::string patchFile);
	~SoundEngine();

	float getNextSample();

	//TEMPORARY
	void processCommand(int type, int channel, int keyNum);
};

