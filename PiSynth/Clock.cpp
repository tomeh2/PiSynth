#include "Clock.h"

int Clock::clock;
int Clock::sampleRate;

void Clock::initialize(int sampleRate)
{
	Clock::sampleRate = sampleRate;
	Clock::clock = 0;
}

int Clock::getClockSignal()
{
	return Clock::clock;
}

void Clock::updateClock()
{
	Clock::clock++;

	if (Clock::clock == Clock::sampleRate * 4)
		Clock::clock = 0;
}