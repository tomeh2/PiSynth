#include "FileOut.h"
#include "Encoder.h"

FileOut::FileOut(std::string filename)
{
	this->fileOut = std::ofstream(filename, std::ios::binary);
}

FileOut::~FileOut()
{
	this->fileOut.close();
}

void FileOut::writeOut(float* buffer, int size)
{
	char codedSignal[size * 2];
	Encoder::formatToPCM16(buffer, codedSignal, size);

	this->fileOut.write(codedSignal, size * 2);
	this->fileOut.flush();
}
