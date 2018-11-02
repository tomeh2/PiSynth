#include <iostream>

#include "Algorithm.h"

#include "Logger.h"
#include "AlgorithmGenerator.h"

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

float* render(Algorithm* cascade)
{
	float* samples = new float[SAMPLES];

	for (int i = 0; i < SAMPLES; i++)
	{
		samples[i] = cascade->getNextSample();
	}

	return samples;
}

int main()
{
	Algorithm* alg = AlgorithmGenerator::generateAlgorithmFromString(SR, "p(c(1,2),c(3,4))", 4);

	alg->getOperators()[0]->setFrequency(1000.0f);
	alg->getOperators()[1]->setFrequency(1000.0f);
	alg->getOperators()[2]->setFrequency(2000.0f);
	alg->getOperators()[3]->setFrequency(2000.0f);

	ofstream out("/home/pi/Desktop/Shared/data.bin", ios::out | ios::binary);

	if (!out.is_open())
	{
		cout << "File not open SCREEEEkkEEEE!\n";
		cin.get();
		return 0;
	}

	auto start = chrono::high_resolution_clock::now();
	
	float* samples = render(alg);
	char* data = format(samples, SAMPLES);

	auto end = chrono::high_resolution_clock::now();
	auto dur = end - start;
	auto ms = chrono::duration_cast<std::chrono::milliseconds>(dur).count();

	cout << "Time Elapsed: " << ms << " ms\n";

	out.write(data, SAMPLES);

	out.close();

	delete alg;
	delete[] samples;
	delete[] data;

	cin.get();
	return 0;

	cin.get();
}