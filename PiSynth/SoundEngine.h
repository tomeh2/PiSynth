#pragma once

#include "Renderer.h"
#include "InputInterface.h"
#include "OutputInterface.h"

#include <pthread.h>

class SoundEngine
{
private:
	Renderer* audioRenderer;

	InputInterface* inputStream;
	OutputInterface* outputStream;

	pthread_t engineThread;		//Thread ID on which the main loop runs
	bool interrupt;		//Wether the main loop has been interrupted (stopped)

	/*
	* Starts the thread which runs the main loop
	*/
	static void* startEngineThread(void* p);

	/*
	* Contains the main loop which listens to inputs and creates output while running
	*/
	void mainLoop();
	inline void writeToOutput(float* buffer, int bufferSize);
	inline void calculateSamples(float* buffer, int numOfSamples);
	inline void processInputs(int currentTime);
public:
	SoundEngine(int sampleRate, int numChannels, int ppc, std::string patchFile);
	~SoundEngine();

	void start(InputInterface* in, OutputInterface* out);
	void stop();
	float getNextSample();
};

