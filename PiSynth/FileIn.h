#pragma once
#include "OutputInterface.h"

class FileIn : public OutputInterface
{
public:
	FileIn();
	~FileIn();

	void writeOut(float* samples, int size);
	void setCurrentTimestamp();
};

