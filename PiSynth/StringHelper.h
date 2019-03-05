#pragma once

#include <string>

class StringHelper
{
public:
	/*
	Splits the given string (original) into two strings at the character specified by the splitAt variable.
	Character given to splitAt WILL BE IGNORED!

	NOTE: S1 AND S2 MUST BE REFRENCES TO ALREADY EXISTING STRING OBJECTS!

	@param original -> original string which is to be split
	@param splitAt -> character which is where the split will occur
	@param s1 -> first half of the string which has been split (before the given character)
	@param s2 -> second half of the string which has been split (after the given character)
	*/
	static void split(std::string original, char splitAt, std::string* s1, std::string *s2);
};

