#pragma once

#include <vector>
#include <string>

class StringHelper
{
public:
	static void splitLine(std::string str, char splitChar, std::string& s1, std::string& s2);
	/*
	Splits the string into substrings, and returns the substrings as a vector of strings.
	Strings are split at every character that matches splitChar.

	@param str -> string which is to be split
	@param splitChar -> at which character the string will be split
	@returns -> vector of substrings without the 
	*/
	static std::vector<std::string> fragmentString(std::string str, char splitChar);

	/*
	Splits the string based on the character given as the splitChar argument and
	tries to make integers out of the substrings. The resulting integers
	are put into a vector and returned.

	@param str -> string which is to be parsed
	@param splitChar -> char that separates the integers in the given string
	@returns -> integer vector that holds all parsed integers
	*/
	static std::vector<int> strToIntVector(std::string str, char splitChar);

	/*
	Splits the string based on the character given as the splitChar argument and
	tries to make floats out of the substrings. The resulting floats
	are put into a vector and returned.

	@param str -> string which is to be parsed
	@param splitChar -> char that separates the floats in the given string
	@returns -> float vector that holds all parsed integers
	*/
	static std::vector<float> strToFloatVector(std::string str, char splitAt);

	/*
	Removes whitespaces and tabs from the given string and returns the modified string.

	@returns -> string without whitespace or tab characters
	*/
	static std::string removeWhitespace(std::string str);
};