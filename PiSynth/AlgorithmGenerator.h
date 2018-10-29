#pragma once

#include "Block.h"
#include "Operator.h"

#include <vector>
#include <string>

class AlgorithmGenerator
{
private:
	static std::vector<std::string> splitArgs(std::string arguments);
	static Block* generateAlgorithm(Operator* operators, std::string algDescription);
public:
	static bool isPositiveNumber(std::string str);
	static int strToPositiveNum(std::string str);
	static Block* generateAlgorithmFromString(int sampleRate, std::string algDescription, int operatorCount);
};

