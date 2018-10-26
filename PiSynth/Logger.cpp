#include "Logger.h"

#include <iostream>
#include <ctime>

using namespace std;

string getCurrentTimeAsString()
{
	char tm[10];		//holds current time as text
	time_t now = time(0);
	int hour, minute, second;

	hour = (now / 3600) % 24 + 2;		//my timezone (will be made better)
	minute = (now / 60) % 60;
	second = now % 60;

	sprintf(tm, "[%02d:%02d:%02d]", hour, minute, second);

	return std::string(tm);
}

/**
Prints a formatted message. The format is as following:
"[Time] message\n"

Example for message "yay logging":
[13:24:53] yay logging
*/
void Logger::print(std::string message)
{
	cout << getCurrentTimeAsString() << " " << message << "\n";
}