#pragma once

#include <string>

class Logger
{
private:
public:
	static void print(std::string message);
	static void printError(int errCode, std::string errMessage);
};

