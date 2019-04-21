
#include <iostream>

#include "Logger.h"
#include "SoundEngine.h"
#include "Patch.h"
#include "FileIn.h"
#include "FileOut.h"
#include "PatchFileLoader.h"

#include "MidiFile.h"
#include "MidiEvent.h"

#include <fstream>
#include <chrono>
#include <queue>
#include <algorithm>

#include "Clock.h"
#include "FastMath.h"

#define SR 44100
#define RENDER_TIME 180
#define SAMPLES 44100 * RENDER_TIME

#define DEBUG 2

using namespace std;
using namespace smf;

char* format(float* nums, int size)
{
	char* data = new char[size * 2];

	for (int i = 0; i < size * 2; i++)
	{
		data[i] = 0;
	}

	int counter = 0;
	for (int i = 0; i < size; i++)
	{
		int sample = (int)(nums[i] * 1500.f);

		data[counter++] |= (sample);
		data[counter++] |= (sample >> 8);
	}
	return data;
}

float* render(SoundEngine* v, MidiEventList& evnts, InputInterface& inputStream)
{
	float* samples = new float[SAMPLES];
	float dec = 0.0f;
	int ind = 1, var = 0;
	bool temp = true;
#if DEBUG == 2
	for (int i = 0; i < SAMPLES; i++)
	{
		if (temp && inputStream.isActive())
		{
			while (inputStream.ready(var))
			{
				smf::MidiEvent e = inputStream.getNextEvent();
				//v->processCommand(e.getCommandByte() & 0xF0, e.getChannel(), e.getKeyNumber());
				ind++;
			}
			temp = false;
		}

		samples[i] = v->getNextSample();
		dec += 0.045f;

		Clock::updateClock();

		if (dec >= 1.0f)
		{
			dec -= 1.0f;
			var++;
			temp = true;
		}
	}
#endif
#if DEBUG == 1
	MidiEvent e = evnts[0];
	for (int i = 0; i < SAMPLES; i++)
	{
		if (evnts[ind].tick < (int) var && ind < evnts.getSize() - 1)
		{
			e = evnts[ind++];
			v->processCommand(e.getCommandByte() & 0xF0, e.getChannel(), e.getKeyNumber());
		}
		
		samples[i] = v->getNextSample();
		dec += 0.045f;

		Clock::updateClock();

		if (dec >= 1.0f)
		{
			dec -= 1.0f;
			var++;
		}

		if (i % 88200 == 0)
			std::cout << i / (441.f * RENDER_TIME) << "%\n";
		
	}
#endif
#if DEBUG == 0
	for (int i = 0; i < SAMPLES; i++)
	{
		
		if (i == SR * 1)
			v->processCommand(0x90, 0, 40);
		if (i == SR * 5)
			v->processCommand(0x80, 0, 40);
		if (i == SR * 8)
			v->processCommand(0x90, 0, 30);
		if (i == SR * 9)
			v->processCommand(0x80, 0, 30);
		if (i == SR * 15)
			v->processCommand(0x90, 0, 57);
		if (i == SR * 17)
			v->processCommand(0x90, 0, 69);
		if (i == SR * 20)
			v->processCommand(0x80, 0, 57);
		if (i == SR * 21)
			v->processCommand(0x80, 0, 69);
		
		samples[i] = v->getNextSample();
		Clock::updateClock();
	}
#endif
	return samples;
}

int main()
{
	Clock::initialize(SR);
	SoundEngine eng(SR, 16, 32, "/home/pi/Desktop/0.ptch");

	InputInterface* in = new FileIn("/home/pi/Desktop/Shared/edited.mid");
	OutputInterface* out = new FileOut("/home/pi/Desktop/Shared/data.bin");

	auto start = chrono::high_resolution_clock::now();

	eng.start(in, out);

	auto end = chrono::high_resolution_clock::now();

	auto dur = end - start;
	auto ms = chrono::duration_cast<std::chrono::milliseconds>(dur).count();

	cout << "Time Elapsed: " << ms / 1000.0f << " sec\n";

	cin.get();
	
	delete in;
	delete out;

	return 0;
}

int main2()
{
	MidiFile file;
	file.read("/home/pi/Desktop/Shared/edited.mid");

	file.joinTracks();
	file.sortTracks();
	file.absoluteTicks();

	Clock::initialize(SR);
	SoundEngine eng(SR, 16, 32, "/home/pi/Desktop/0.ptch");

	ofstream out("/home/pi/Desktop/Shared/data.bin", ios::out | ios::binary);

	if (!out.is_open())
	{
		cout << "File not open SCREEEEkkEEEE!\n";
		cin.get();
		return 0;
	}

	auto start = chrono::high_resolution_clock::now();

	FileIn f("/home/pi/Desktop/Shared/edited.mid");
	float* samples = render(&eng, file[0], f);

	auto end = chrono::high_resolution_clock::now();

	char* data = format(samples, SAMPLES);

	auto dur = end - start;
	auto ms = chrono::duration_cast<std::chrono::milliseconds>(dur).count();

	cout << "Time Elapsed: " << ms / 1000.0f << " sec\n";

	out.write(data, SAMPLES * 2);

	out.close();

	delete[] samples;
	delete[] data;

	cin.get();
	return 0;
}