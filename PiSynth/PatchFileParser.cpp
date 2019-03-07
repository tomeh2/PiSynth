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
	std::string s1, s2, line;

	do
	{
		line = getLine();
		if (line.compare("file_end") == 0)
			break;

		line.erase(line.size() - 1, 1);
		
		if (line.find(""))

		s1 = line.substr(0, splitIndex);
		s2 = line.substr(splitIndex + 1, line.size() - 1);

		this->properties.insert(std::pair<std::string, std::string>(s1, s2));

		std::cout << s1 << " | " << s2 << "\n";
	} while (line.compare("file_end") != 0);

	for (std::map<std::string, std::string>::iterator it = this->properties.begin(); it != this->properties.end(); it++)
	{
		std::cout << it->first << " | " << it->second << "\n";
	}
}

//------------------------------- PUBLIC --------------------------------//

std::map<std::string, std::string> PatchFileParser::getFileData()
{
	parseFile();
	return this->properties;
}