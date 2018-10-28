#include "AlgorithmGenerator.h"

#include <iostream>
#include <sstream>

Block* AlgorithmGenerator::generateAlgorithmFromString(std::string algDescription, int operatorCount)
{
	char command = algDescription.at(0);
	algDescription = algDescription.substr(2, algDescription.size() - 3);
	std::vector<std::string> args = splitArgs(algDescription);

	std::cout << "Command: " << command << "\n";
	std::cout << "Size: " << args.size() << "\n";

	for (int j = 0; j < 5; j++)
	{
		std::cout << args.at(j) << " | ";
	}

	return nullptr;
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