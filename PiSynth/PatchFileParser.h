#pragma once

#include <fstream>
#include <map>

class PatchFileParser
{
private:
	std::ifstream* patchFileStream;
	std::map<std::string, std::string> properties;

	void loadFile(std::string filename);
	void parseFile();	//STARTS PARSING THE FILE AND SAVES THE DATA INTO THE PROPERTIES MAP
	std::string getLine();		//Returns the next line and moves the file pointer to the beginning of the new line
public:
	PatchFileParser(std::string filename);
	~PatchFileParser();

	std::map<std::string, std::string> getFileData();
};

