
#include <iostream>

#include "Logger.h"
#include "SoundEngine.h"
#include "FileIn.h"
#include "FileOut.h"

#include <chrono>

#define SR 44100

int main()
{
	SoundEngine eng(SR, 16, 32, "/home/pi/Desktop/p3.ptch");

	InputInterface* in = new FileIn("/home/pi/Desktop/Shared/edited.mid");
	OutputInterface* out = new FileOut("/home/pi/Desktop/Shared/data.bin");

	auto start = std::chrono::high_resolution_clock::now();

	eng.start(in, out);

	auto end = std::chrono::high_resolution_clock::now();

	auto dur = end - start;
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

	std::cout << "Time Elapsed: " << ms / 1000.0f << " sec\n";

	std::cin.get();

	return 0;
}