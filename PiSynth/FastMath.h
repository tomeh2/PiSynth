#pragma once

#include "Logger.h"

#include <math.h>

class FastMath
{
private:
	static int sr;
	static float* sineVals;
public:
	static void initialize(int sampleRate);
	static void destroy();
	static float fastSin(float val);
	static float fastSinI(int val);
};