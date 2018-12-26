
#include <iostream>

#include "Logger.h"
#include "Renderer.h"
#include "Patch.h"

#include "MidiFile.h"
#include "MidiEvent.h"

#include <fstream>
#include <chrono>
#include <queue>
#include <algorithm>

#include "Clock.h"
#include "FastMath.h"

#define SR 44100
#define RENDER_TIME 220
#define SAMPLES 44100 * RENDER_TIME

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
	/*
	Operator op(44100);

	for (int i = 0; i < SAMPLES; i++)
	{
		
		if (i == SR * 1)
			op.trigger();
		if (i == SR * 5)
			op.release();
		if (i == SR * 8)
			op.trigger();
		if (i == SR * 9)
			op.release();
		if (i == SR * 15)
			op.trigger();
		if (i == SR * 17)
			op.trigger();
		if (i == SR * 20)
			op.release();
		
		samples[i] = op.getNextSample(0.0f);
		Clock::updateClock();
	}*/
	
	return samples;
}

int main2()
{
	Patch patch;

	patch.setAlgDescription("p(1, 2)");
	patch.setOperatorCount(2);

	patch.setFreqRatio(0, 1.f);
	patch.setFreqRatio(1, 2.f);

	patch.setOutputLevel(0, 1.f);
	patch.setOutputLevel(1, 0.5f);

	patch.addEnvelopeSegment(0, 0.02f, 1.f, 0.f);
	patch.addEnvelopeSegment(0, -0.3f, 0.7f, 0.f);
	patch.addEnvelopeSegment(0, 0.f, 0.7f, 0.f);
	patch.addEnvelopeSegment(0, -0.1f, 0.f, 0.f);

	patch.addEnvelopeSegment(1, 0.2f, 1.f, 0.f);
	patch.addEnvelopeSegment(1, -0.03f, 0.4f, 0.f);
	patch.addEnvelopeSegment(1, 0.f, 0.4f, 0.f);
	patch.addEnvelopeSegment(1, -0.1f, 0.f, 0.f);

	patch.printPatchData();

	std::cin.get();
}

int main()
{
	MidiFile file;
	file.read("/home/pi/Desktop/Shared/edited.mid");

	file.joinTracks();
	file.sortTracks();
	file.absoluteTicks();

	Patch patch;

	patch.setAlgDescription("p(c(1, 2, 3, f(4)))");
	patch.setOperatorCount(4);

	patch.setFreqRatio(0, 8.f);
	patch.setFreqRatio(1, 16.f);
	patch.setFreqRatio(2, 1.f);
	patch.setFreqRatio(3, 0.5f);

	patch.setOutputLevel(0, 1.f);
	patch.setOutputLevel(1, 0.7f);
	patch.setOutputLevel(2, 1.f);
	patch.setOutputLevel(3, 0.8f);

	patch.setModulationSensitivity(0, 1.f);
	patch.setModulationSensitivity(1, 1.f);
	patch.setModulationSensitivity(2, 1.f);
	patch.setModulationSensitivity(3, 1.f);

	patch.addEnvelopeSegment(3, 0.002f, 0.5f, 0.f);
	patch.addEnvelopeSegment(3, -0.02f, 0.0f, 0.f);

	patch.addEnvelopeSegment(2, 0.002f, 0.3f, 0.f);
	patch.addEnvelopeSegment(2, -0.02f, 0.0f, 0.f);

	patch.addEnvelopeSegment(1, 0.004f, 1.f, 0.f);
	patch.addEnvelopeSegment(1, -0.05, 0.5f, 0.f);
	patch.addEnvelopeSegment(1, -0.3, 0.f, 0.f);
	patch.addEnvelopeSegment(1, -0.05, 0.f, 0.f);

	patch.addEnvelopeSegment(0, 0.004f, 1.f, 0.f);
	patch.addEnvelopeSegment(0, -0.02, 0.35f, 0.f);
	patch.addEnvelopeSegment(0, -0.3, 0.f, 0.f);
	patch.addEnvelopeSegment(0, -0.02, 0.f, 0.f);

	Clock::initialize(SR);
	Renderer r(SR, 16, 32, patch);

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

	delete[] samples;
	delete[] data;

	cin.get();
	return 0;
}