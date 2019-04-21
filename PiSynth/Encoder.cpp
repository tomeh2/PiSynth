#include "Encoder.h"

void Encoder::formatToPCM16(float* buffer, char* destination, int bufferSize)
{
	int counter = 0;
	for (int i = 0; i < bufferSize; i++)
	{
		int sample = (int)(buffer[i]);

		destination[counter++] = (sample);
		destination[counter++] = (sample >> 8);
	}
}