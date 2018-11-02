#pragma once

#include "Block.h"
#include "Operator.h"
#include "Algorithm.h"

#include <vector>
#include <string>

class AlgorithmGenerator
{
private:
	static std::vector<std::string> splitArgs(std::string arguments);
	static Block* generateAlgorithm(Operator** operators, std::string algDescription);
	static bool isPositiveNumber(std::string str);
	static int strToPositiveNum(std::string str);
public:
	/**
	Generates an algorithm from the given algorithm description string.

	@param sampleRate
	@param algDescription -> string which holds the description of the algorithm (connection between operators)
	@param operatorCound -> how many operators are used in the algorithm
	*/
	static Algorithm* generateAlgorithmFromString(int sampleRate, std::string algDescription, int operatorCount);
};

