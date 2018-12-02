
#include <iostream>

#include "Logger.h"
#include "Renderer.h"

#include "MidiFile.h"
#include "MidiEvent.h"

#include <fstream>
#include <chrono>
#include <queue>
#include <algorithm>

#include "Clock.h"
#include "FastMath.h"

#define SR 44100
#define SAMPLES 44100 * 180

using namespace std;
using namespace smf;

void test()
{
	Logger::print("yeeeeeee");
	cin.get();
}

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
		int sample = (int)(nums[i] * 1000.0f);

		data[counter++] |= (sample);
		data[counter++] |= (sample >> 8);
	}
	return data;
}

float* render(Renderer* v, MidiEventList& evnts)
{
	float* samples = new float[SAMPLES];
	float dec = 0.0f;
	
	MidiEvent e = evnts[0];
	int ind = 1, var = 0;
	for (int i = 0; i < SAMPLES; i++)
	{
		if (evnts[ind].tick < (int) var && ind < evnts.getSize() - 1)
		{
			e = evnts[ind++];
			v->processCommand(e.getCommandByte() & 0xF0, e.getChannel(), e.getKeyNumber());
		}
		
		samples[i] = v->getNextSample();
		dec += 0.05f;

		Clock::updateClock();

		if (dec >= 1.0f)
		{
			dec -= 1.0f;
			var++;
		}
	}
	
	/*
	
	for (int i = 0; i < SAMPLES; i++)
	{
		
		if (i == SR * 1)
			v->processCommand(0x90, 0, 44);
		if (i == SR * 3)
			v->processCommand(0x80, 0, 44);
		if (i == SR * 4)
			v->processCommand(0x90, 0, 44);
		if (i == SR * 7)
			v->processCommand(0x80, 0, 44);
			
		samples[i] = v->getNextSample();
	}*/
	
	return samples;
}

int main()
{
	MidiFile file;
	file.read("/home/pi/Desktop/Shared/edited.mid");

	file.joinTracks();
	file.sortTracks();
	file.absoluteTicks();
	int ind = 0;

	for (int i = 0; i < file.getTrackCount(); i++)
	{
		
	}

	FastMath::initialize(SR);
	Clock::initialize(SR);
	Renderer r(SR, 16, 32);

	ofstream out("/home/pi/Desktop/Shared/data.bin", ios::out | ios::binary);

	if (!out.is_open())
	{
		cout << "File not open SCREEEEkkEEEE!\n";
		cin.get();
		return 0;
	}

	auto start = chrono::high_resolution_clock::now();

	float* samples = render(&r, file[0]);

	auto end = chrono::high_resolution_clock::now();

	char* data = format(samples, SAMPLES);

	auto dur = end - start;
	auto ms = chrono::duration_cast<std::chrono::milliseconds>(dur).count();

	cout << "Time Elapsed: " << ms / 1000.0f << " sec\n";

	out.write(data, SAMPLES * 2);

	out.close();

	FastMath::destroy();
	delete[] samples;
	delete[] data;

	cin.get();
	return 0;
}