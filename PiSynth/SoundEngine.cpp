#include "SoundEngine.h"
#include "PatchFileLoader.h"
#include "Logger.h"
#include "Clock.h"

#define PATCH_FILE_DEFAULT "/home/pi/Desktop/p2.ptch"

#define BUFFER_SIZE 512

SoundEngine::SoundEngine(int sampleRate, int numChannels, int ppc, std::string patchFile)
{
	Clock::initialize(sampleRate);

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
	delete this->inputStream;
	delete this->outputStream;
}

void SoundEngine::start(InputInterface* in, OutputInterface* out)
{
	this->inputStream = in;
	this->outputStream = out;
	
	pthread_create(&this->engineThread, nullptr, SoundEngine::startEngineThread, this);
	pthread_join(this->engineThread, nullptr);
}

void SoundEngine::stop()
{
	this->interrupt = true;
}

float SoundEngine::getNextSample()
{
	return this->audioRenderer->getNextSample();
}

//--------------------- THREAD RELATED FUNCTIONS ---------------------//

void* SoundEngine::startEngineThread(void* p)
{
	static_cast<SoundEngine*>(p)->mainLoop();
	return nullptr;
}

inline void SoundEngine::writeToOutput(float* buffer, int bufferSize)
{
	this->outputStream->writeOut(buffer, bufferSize);
}

inline void SoundEngine::calculateSamples(float* buffer, int numOfSamples)
{
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		buffer[i] = this->audioRenderer->getNextSample() * 2500.f;
		Clock::updateClock();
	}
}

inline void SoundEngine::processInputs(int currentTime)
{
	while (this->inputStream->ready(currentTime))
	{
		smf::MidiEvent evnt = this->inputStream->getNextEvent();
		this->audioRenderer->processCommand(evnt.getCommandByte() & 0xF0, evnt.getChannel(), evnt.getKeyNumber());
	}
}

void SoundEngine::mainLoop()
{
	int currentTime = 0;
	float buffer[BUFFER_SIZE] = { 0.f };

	while (this->inputStream->isActive() && currentTime < 100000 && !this->interrupt)
	{
		this->processInputs(currentTime);
		this->calculateSamples(buffer, BUFFER_SIZE);
		this->writeToOutput(buffer, BUFFER_SIZE);

		currentTime += 23;
	}
	this->interrupt = false;
}