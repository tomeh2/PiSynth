#pragma once

#include "Block.h"

#include <vector>
#include <string>

class AlgorithmGenerator
{
private:
	static std::vector<std::string> splitArgs(std::string arguments);
public:
	static Block* generateAlgorithmFromString(std::string algDescription, int operatorCount);
};

