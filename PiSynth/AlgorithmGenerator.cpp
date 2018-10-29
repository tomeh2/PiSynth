#include "AlgorithmGenerator.h"

#include "Cascade.h"
#include "Parallel.h"
#include "Feedback.h"
#include "Logger.h"

#include <iostream>
#include <sstream>

Block* AlgorithmGenerator::generateAlgorithmFromString(int sampleRate, std::string algDescription, int operatorCount)
{
	Operator* operators[operatorCount];

	for (int i = 0; i < operatorCount; i++)
		operators[i] = new Operator(sampleRate);

	std::cout << "Address: " << operators[0] << "\n";
	std::cout << "Address: " << operators[1] << "\n";

	return generateAlgorithm(*operators, algDescription);
} 

Block* AlgorithmGenerator::generateAlgorithm(Operator* operators, std::string algDescription)
{
	char command = algDescription.at(0);
	algDescription = algDescription.substr(2, algDescription.size() - 3);
	std::vector<std::string> args = splitArgs(algDescription);

	switch (command)
	{
	case 'c':		//CASCADE
		{
			Cascade* cascade = new Cascade();
			for (std::string arg : args)
			{
				if (isPositiveNumber(arg))
					cascade->addBlock((Block*)&operators[strToPositiveNum(arg) - 1]);
				else
					generateAlgorithm(operators, arg);
			}
			return (Block*)cascade;
		}
	case 'p':		//PARALLEL
		{
			Parallel* parallel = new Parallel();
			for (std::string arg : args)
			{
				if (isPositiveNumber(arg))
					parallel->addBlock((Block*)&operators[strToPositiveNum(arg) - 1]);
				else
					generateAlgorithm(operators, arg);
			}
			//return (Block*)&parallel;
		}
	case 'f':		//FEEDBACK
		{
			Feedback* feedback = new Feedback();
			for (std::string arg : args)
			{
				if (isPositiveNumber(arg))
					feedback->setBlock((Block*)&operators[strToPositiveNum(arg) - 1]);
				else
					generateAlgorithm(operators, arg);
			}
			//return (Block*)&feedback;
		}	
	default:
		{
			Logger::print("AlgorithmGenerator -> command not recognized!");
			//return nullptr;
		}
	}
	//return nullptr;
}

bool AlgorithmGenerator::isPositiveNumber(std::string str)
{
	bool valid = true;

	for (int i = 0; i < str.size(); i++)
		if (!isdigit(str[i]))
		{
			valid = false;
			break;
		}

	return valid;
}

int AlgorithmGenerator::strToPositiveNum(std::string str)
{
	if (isPositiveNumber(str))
		return std::stoi(str);
	else
		return -1;
}

std::vector<std::string> AlgorithmGenerator::splitArgs(std::string arguments)
{
	int depth = 0;
	std::vector<std::string> args;
	std::stringstream ss;
	ss.str("");
	
	for (int i = 0; i < arguments.size(); i++)
	{
		char temp = arguments.at(i);

		if (temp == ' ')
			continue;
		if (temp == '(')
			depth++;
		if (temp == ')')
			depth--;
	
		if (temp == ',' && depth == 0)
		{
			args.push_back(ss.str());
			ss.str("");
		}
		else
			ss << temp;

		if (i == arguments.size() - 1)
		{
			args.push_back(ss.str());
			ss.str("");
		}
	}
	return args;
}