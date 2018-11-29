#include "Algorithm.h"
#include "Logger.h"

Algorithm::Algorithm(Operator** operators, Block* algorithm, int operatorCount)
{
	this->operators = operators;
	this->algorithm = algorithm;

	this->operatorCount = operatorCount;
}

Algorithm::~Algorithm()
{
	Logger::print(std::string(std::to_string(operatorCount)).c_str());
	for (int i = 0; i < this->operatorCount; i++)
		delete this->operators[i];

	delete this->operators;
	delete this->algorithm;
}

float Algorithm::getNextSample()
{
	return this->algorithm->getNextSample(0.0f);
}

Operator** Algorithm::getOperators()
{
	return this->operators;
}

int Algorithm::getOperatorCount()
{
	return this->operatorCount;
}