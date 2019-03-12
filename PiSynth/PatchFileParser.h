#pragma once

#include "Patch.h"

#include <fstream>
#include <map>
#include <vector>

class PatchFileParser
{
private:
	static Patch createPatchFromData(std::map<std::string, std::string> data);

	static std::vector<int> strToIntVector(std::string str);
	static std::string getLine(std::ifstream& file);		//Returns the next line and moves the file pointer to the beginning of the new line
	static void splitLine(std::string str, char splitChar, std::string& s1, std::string& s2);
	static std::string removeWhitespace(std::string str);
	static void parseHeader(std::ifstream& file);
	static void parseInstruments(std::ifstream& file);
	static void parseFile(std::ifstream& file);	//Starts parsing the data and returns the map containing all the retrieved data
public:
	static std::vector<Patch> loadPatchData(std::string filename);
};

