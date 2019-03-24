#include "SoundEngine.h"
#include "PatchFileLoader.h"
#include "Logger.h"

#define PATCH_FILE_DEFAULT "/home/pi/Desktop/p2.ptch"

SoundEngine::SoundEngine(int sampleRate, int numChannels, int ppc, std::string patchFile)
{
	std::vector<Patch> patches = PatchFileLoader::loadPatchData(patchFile);
	if (patches.size() == 0)
	{
		Logger::print("Loading the default patch file instead...");
		patches = PatchFileLoader::loadPatchData(PATCH_FILE_DEFAULT);
	}

	this->audioRenderer = new Renderer(sampleRate, numChannels, ppc, patches[0]);
}

SoundEngine::~SoundEngine()
{
	delete this->audioRenderer;
}

float SoundEngine::getNextSample()
{
	return this->audioRenderer->getNextSample();
}

void SoundEngine::processCommand(int type, int channel, int keyNum)
{
	this->audioRenderer->processCommand(type, channel, keyNum);
}