#include <iostream>

#include "Operator.h"
#include "Cascade.h"
#include "Parallel.h"
#include "Feedback.h"
#include "Logger.h"
#include "AlgorithmGenerator.h"

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

float* render(Feedback* cascade)
{
	float* samples = new float[441000];

	for (int i = 0; i < 441000; i++)
	{
		samples[i] = cascade->getNextSample(0.0f);
	}

	return samples;
}

int main()
{
	AlgorithmGenerator::generateAlgorithmFromString("c(1,p(2,f(3),4),c(5,f(6)),7,8)", 8);
	/*
	Operator op1(44100);
	Operator op2(44100);
	Operator op3(44100);

	Block* b1 = &op1;
	Block* b2 = &op2;
	Block* b3 = &op3;

	op1.setWaveform(SINE_WAVE);
	op1.setFrequency(400.0f);
	op2.setWaveform(SINE_WAVE);
	op2.setFrequency(200.0f);
	op3.setWaveform(SINE_WAVE);
	op3.setFrequency(100.0f);

	Feedback fb;

	fb.setBlock(&op1);

	ofstream out("/home/pi/Desktop/data.bin", ios::out | ios::binary);

	if (!out.is_open())
	{
		cout << "File not open SCREEEEkkEEEE!\n";
		cin.get();
		return 0;
	}

	auto start = chrono::high_resolution_clock::now();
	
	float* samples = render(&fb);
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
	return 0;*/

	cin.get();
}