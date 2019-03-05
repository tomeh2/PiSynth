#include "PatchFileParser.h"

//TODO: ADD ERROR CHECKING!!!
#include <iostream>

PatchFileParser::PatchFileParser(std::string filename)
{
	this->loadFile(filename);

	if (!this->patchFileStream->is_open())
	{
		std::cout << "FILE NOT OPEN!\n";
		return;
	}
}

PatchFileParser::~PatchFileParser()
{
	this->patchFileStream->close();
	delete this->patchFileStream;
}

//------------------------------- PRIVATE -------------------------------//
void PatchFileParser::loadFile(std::string filename)
{
	this->patchFileStream = new std::ifstream(filename);
}

std::string PatchFileParser::getLine()
{
	char str[128];
	this->patchFileStream->getline(str, 128);
	return std::string(str);
}

void PatchFileParser::parseFile()
{
	std::string s1, s2;

	for (int i = 0; i < 5; i++) {
		std::string line = getLine();

		line.erase(line.size() - 1, 1);
		int splitIndex = line.find('=');
		s1 = line.substr(0, splitIndex);
		s2 = line.substr(splitIndex + 1, line.size() - 1);

		std::cout << s1 << " | " << s2 << "\n";
	}
}

//------------------------------- PUBLIC --------------------------------//

std::map<std::string, std::string> PatchFileParser::getFileData()
{
	parseFile();
	return this->properties;
}