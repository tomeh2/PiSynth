#pragma once

#include <string>

class Logger
{
private:
public:
	static void print(const char* message);
	static void nfprint(const char* message);
	static void slprint(const char* message);
};

