#include <iostream>

#include "WaveGenerator.h"
#include "Logger.h"

#include <fstream>
#include <chrono>

using namespace std;

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
		int sample = (int)(nums[i] * 10000.0f);

		data[counter++] |= (sample);
		data[counter++] |= (sample >> 8);
	}
	return data;
}

float* render(WaveGenerator* wg)
{
	float* samples = new float[441000];

	for (int i = 0; i < 441000; i++)
	{
		samples[i] = wg->getNextSample();
	}

	return samples;
}

int main()
{
	WaveGenerator waveGenerator(44100);

	waveGenerator.setOscillatorType(SQUARE_WAVE);

	ofstream out("/home/pi/Desktop/data.bin", ios::out | ios::binary);

	if (!out.is_open())
	{
		cout << "File not open SCREEEEkkEEEE!\n";
		cin.get();
		return 0;
	}

	auto start = chrono::high_resolution_clock::now();

	float* samples = render(&waveGenerator);
	char* data = format(samples, 441000);

	auto end = chrono::high_resolution_clock::now();
	auto dur = end - start;
	auto ms = chrono::duration_cast<std::chrono::milliseconds>(dur).count();

	cout << "Time Elapsed: " << ms << " ms\n";

	out.write(data, 882000);

	out.close();

	delete[] samples;
	delete[] data;

	cin.get();
	return 0;
}