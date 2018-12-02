#include "FastMath.h"

float* FastMath::sineVals;
int FastMath::sr;

void FastMath::initialize(int sampleRate)
{
	Logger::print("Started initialization of FastMath...");
	sr = sampleRate;
	sineVals = new float[sampleRate];

	Logger::print("Precalculating sine values...");
	//Precalculate sine values
	for (int i = 0; i < sampleRate; i++)
		sineVals[i] = sin(2.f * M_PI / sampleRate * 4 * i);
	Logger::print("Initialization of FastMath complete!");
}

void FastMath::destroy()
{
	delete[] sineVals;
}

float FastMath::fastSin(float val)
{
	if (val >= 0.f && val < M_PI * 2.f)
		return sineVals[int(val / (2 * M_PI) * sr)];
}

/*
This function expects to get a val between 0 and Sample Rate.
It returns the precalculated value of sine.
*/
float FastMath::fastSinI(int val)
{
	if (val < 0)
		return sineVals[sr - abs(val % sr)];
	else
		return sineVals[val % sr];
}