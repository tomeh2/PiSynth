#pragma once
class Clock
{
private:
	static int sampleRate;
	static int clock;
public:
	static void initialize(int sampleRate);
	static int getClockSignal();
	static void updateClock();
};

