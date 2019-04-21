#pragma once

#include "OutputInterface.h"

#include <fstream>

class FileOut : public OutputInterface
{
private:
	std::ofstream fileOut;
public:
	FileOut(std::string filename);
	~FileOut();

	void writeOut(float* buffer, int size);
};

