#include "StringHelper.h"

#include <ctype.h>
#include <sstream>

#define MAX_LINE_LEN 128

std::vector<std::string> StringHelper::fragmentString(std::string str, char splitAt)
{
	std::vector<std::string> stringFragments;
	std::stringstream ss;

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == splitAt || i == str.size() - 1)
		{
			if (i == str.size() - 1 && str[i] != splitAt)
				ss << str[i];
			
			stringFragments.push_back(ss.str());
			ss.str("");
		}
		else
			ss << str[i];
	}
	return stringFragments;
}

std::vector<int> StringHelper::strToIntVector(std::string str, char splitAt)
{
	std::vector<int> parsedInts;
	std::vector<std::string> stringFragments = fragmentString(str, splitAt);

	for (int i = 0; i < stringFragments.size(); i++)
	{
		parsedInts.push_back(std::stoi(stringFragments[i]));
	}
	return parsedInts;
}

std::vector<float> StringHelper::strToFloatVector(std::string str, char splitAt)
{
	std::vector<float> parsedFloats;
	std::vector<std::string> stringFragments = fragmentString(str, splitAt);

	for (int i = 0; i < stringFragments.size(); i++)
	{
		parsedFloats.push_back(std::stof(stringFragments[i]));
	}
	return parsedFloats;
}

std::string StringHelper::removeWhitespace(std::string str)
{
	char temp[MAX_LINE_LEN];

	int strIndex = 0;
	for (std::string::iterator it = str.begin(); it != str.end(); it++)
	{
		if (*it == ' ' || *it == '\t')
			continue;
		else
			temp[strIndex++] = *it;
	}
	return std::string(temp);
}