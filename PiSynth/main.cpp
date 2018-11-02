#include <iostream>

#include "Algorithm.h"
#include "AlgorithmGenerator.h"
#include "Logger.h"
#include "Voice.h"

#include <fstream>
#include <chrono>

#define SR 88200
#define SAMPLES 882000

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
		int sample = (int)(nums[i] * 2000.0f);

		data[counter++] |= (sample);
		data[counter++] |= (sample >> 8);
	}
	return data;
}

float* render(Voice* v)
{
	float* samples = new float[SAMPLES];

	for (int i = 0; i < SAMPLES; i++)
	{
		if (i == SR * 1.0f)
			v->keyDown(44);
		if (i == SR * 3.0f)
			v->keyUp();
		if (i == SR * 4.0f)
			v->keyDown(20);
		if (i == SR * 7.0f)
			v->keyUp();

		samples[i] = v->getNextSample();
	}

	return samples;
}

int main()
{
	Algorithm* alg = AlgorithmGenerator::generateAlgorithmFromString(SR, "p(c(1,f(2)),c(3,f(4)))", 4);
	Voice* v = new Voice(alg);


	ofstream out("/home/pi/Desktop/Shared/data.bin", ios::out | ios::binary);

	if (!out.is_open())
	{
		cout << "File not open SCREEEEkkEEEE!\n";
		cin.get();
		return 0;
	}

	auto start = chrono::high_resolution_clock::now();
	
	float* samples = render(v);
	char* data = format(samples, SAMPLES);

	auto end = chrono::high_resolution_clock::now();
	auto dur = end - start;
	auto ms = chrono::duration_cast<std::chrono::milliseconds>(dur).count();

	cout << "Time Elapsed: " << ms << " ms\n";

	out.write(data, SAMPLES);

	out.close();

	delete v;
	delete[] samples;
	delete[] data;

	cin.get();
	return 0;

	cin.get();
}