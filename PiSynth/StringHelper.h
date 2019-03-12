#pragma once

#include <vector>
#include <string>

class StringHelper
{
public:
	static std::vector<std::string> fragmentString(std::string str, char splitChar);
	static std::vector<int> strToIntVector(std::string str, char splitChar);
	static std::vector<float> strToFloatVector(std::string str, char splitAt);
};

