#pragma once

#include <string>

class Logger
{
private:
public:
/**
Prints a formatted message. The format is as following:
"[Time] message\n"

Example for message "yay logging":
[13:24:53] yay logging
*/
	static void print(std::string message);
};

