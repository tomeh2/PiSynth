
#include <iostream>

#include "Logger.h"
#include "Renderer.h"

#include "MidiFile.h"
#include "MidiEvent.h"

#include <fstream>
#include <chrono>
#include <queue>
#include <algorithm>

#define SR 88200
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
		int sample = (int)(nums[i] * 2000.0f);

		data[counter++] |= (sample);
		data[counter++] |= (sample >> 8);
	}
	return data;
}

float* render(Renderer* v, queue<MidiEvent>* evnts)
{
	float* samples = new float[SAMPLES];
	int timing = 0;
	float dec = 0.0f;
	
	for (int i = 0; i < SAMPLES; i++)
	{
		MidiEvent e = evnts->front();
		if (e.tick < timing)
		{
			v->processCommand(e.getCommandByte() & 0xF0, e.getChannel(), e.getKeyNumber());
			evnts->pop();
		}
		samples[i] = v->getNextSample();

		dec += 0.025f;
		if (dec >= 1.0f)
		{
			timing++;
			dec -= 1.0f;
		}
	}
	

	/*
	for (int i = 0; i < SAMPLES; i++)
	{
		
		if (i == SR * 1)
			v->processCommand(0x80, 0, 44);
		if (i == SR * 3)
			v->processCommand(0x80, 0, 20);
		if (i == SR * 4)
			v->processCommand(0x90, 0, 44);
		if (i == SR * 7)
			v->processCommand(0x90, 0, 20);
			
		samples[i] = v->getNextSample();
	}
	*/
	return samples;
}
/*
int main()
{
	Renderer r(44100, 4, 8);

	ofstream out("/home/pi/Desktop/Shared/data.bin", ios::out | ios::binary);

	if (!out.is_open())
	{
		cout << "File not open SCREEEEkkEEEE!\n";
		cin.get();
		return 0;
	}

	auto start = chrono::high_resolution_clock::now();
	
	float* samples = render(&r);
	char* data = format(samples, SAMPLES);

	auto end = chrono::high_resolution_clock::now();
	auto dur = end - start;
	auto ms = chrono::duration_cast<std::chrono::milliseconds>(dur).count();

	cout << "Time Elapsed: " << ms << " ms\n";

	out.write(data, SAMPLES * 2);

	out.close();

	delete[] samples;
	delete[] data;

	cin.get();
	return 0;
}*/
#include <fstream>
int main()
{
	MidiFile file;

	std::cout << file.read("/home/pi/Desktop/edited.mid") << "\n";

	vector<MidiEvent> events;
	
	for (int i = 0; i < file.getTrackCount(); i++)
	{
		for (int j = 0; j < file[i].getEventCount(); j++)
		{
			events.push_back(file[i][j]);
		}
	}
	
	std::sort(events.begin(), events.end(), [](const MidiEvent& a, const MidiEvent& b) -> bool {return a.tick < b.tick; });

	for (auto i = events.begin(); i != events.end(); i++)
		std::cout << i->tick << "\n";

	queue<MidiEvent> ev;
	for (int i = 0; i < events.size(); i++)
	{
		ev.push(events[i]);
	}


	Renderer r(44100, 16, 32);

	ofstream out("/home/pi/Desktop/Shared/data.bin", ios::out | ios::binary);

	if (!out.is_open())
	{
		cout << "File not open SCREEEEkkEEEE!\n";
		cin.get();
		return 0;
	}

	auto start = chrono::high_resolution_clock::now();

	float* samples = render(&r, &ev);

	auto end = chrono::high_resolution_clock::now();

	char* data = format(samples, SAMPLES);

	auto dur = end - start;
	auto ms = chrono::duration_cast<std::chrono::milliseconds>(dur).count();

	cout << "Time Elapsed: " << ms << " ms\n";

	out.write(data, SAMPLES * 2);

	out.close();

	delete[] samples;
	delete[] data;

	cin.get();
	return 0;
}