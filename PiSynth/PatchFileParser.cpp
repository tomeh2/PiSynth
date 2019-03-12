#include "PatchFileParser.h"
#include "Patch.h"

#include <iostream>
#include <map>

#define MAX_LINE_LEN 128

void test(std::map<std::string, std::string> mp)
{
	for (std::map<std::string, std::string>::iterator it = mp.begin(); it != mp.end(); it++)
	{
		std::cout << it->first << " = " << it->second << "\n";
	}
}

//------------------------------- PRIVATE -------------------------------//
Patch PatchFileParser::createPatchFromData(std::map<std::string, std::string> patchData)
{
	Patch p;

	p.setOperatorCount(std::stoi(patchData["opv"]));
	p.setAlgDescription(patchData["alg"]);

	for (int i = 0; i < p.getOperatorCount(); i++)
	{
		p.setFreqRatio(i, std::stof(patchData[std::string("freq_ratio") + std::to_string(i)]));
		p.setOutputLevel(i, std::stof(patchData[std::string("out_lvl") + std::to_string(i)]));
		p.setModulationSensitivity(i, std::stof(patchData[std::string("mod_sens") + std::to_string(i)]));

		for (int j = 0; j < 4; j++)
		{
			//p.addEnvelopeSegment(i,
			//	std::stoi(patchData[std::string("env_rate") + std::to_string(i)]),
			//	std::stof(patchData[std::string("env_lvl") + std::to_string(i)]), 0);
		}
	}
	return p;
}

std::vector<int> PatchFileParser::strToIntVector(std::string str)
{
	std::vector<int> vals;
	std::vector<std::string> test;

	do
	{
		std::string s1, s2;

		splitLine(str, ',', s1, s2);

		str = s2;

		std::cout << s1 << "\n";

		test.push_back(s1);
	} while (str.find(',' != std::string::npos));
}

void PatchFileParser::splitLine(std::string str, char splitChar, std::string& s1, std::string& s2)
{
	int splitIndex = str.find(splitChar);
	s1 = str.substr(0, splitIndex);
	s2 = str.substr(splitIndex + 1, str.size() - splitIndex - 2);
}

std::string PatchFileParser::removeWhitespace(std::string str)
{
	char temp[MAX_LINE_LEN];

	int strIndex = 0;
	for (std::string::iterator it = str.begin(); it != str.end(); it++)
	{
		if (*it == ' ' || *it == '\t')
			continue;
		else
			temp[strIndex++] = *it;
	}
	return std::string(temp);
}

std::string PatchFileParser::getLine(std::ifstream& file)
{
	char str[MAX_LINE_LEN];
	file.getline(str, MAX_LINE_LEN);
	return std::string(str);
}

void PatchFileParser::parseHeader(std::ifstream& file)
{
	std::string s1, s2, line;

	do
	{
		line = getLine(file);
		
		if (line.find("{") != std::string::npos)
			break;
		else
		{
			splitLine(line, '=', s1, s2);

			std::cout << s1 << " = " << s2 << "\n";

			//this->properties.insert(std::pair<std::string, std::string>(s1, s2));
		}
	} while (!file.eof());
	std::cout << "-------------------------------------\n";
}

void PatchFileParser::parseInstruments(std::ifstream& file)
{
	std::map<std::string, std::string> instrumentData;
	std::string s1, s2, line;
	int operatorNum = -1, nestingDepth = 1;

	do
	{
		line = getLine(file);

		if (line.find("{") != std::string::npos)
		{
			operatorNum++;
			nestingDepth++;
			continue;
		}
		else if (line.find("}") != std::string::npos)
		{
			nestingDepth--;
			continue;
		}

		splitLine(line, '=', s1, s2);
		s1 = removeWhitespace(s1);

		if (operatorNum >= 0)
		{
			s1.append(std::to_string(operatorNum));
			instrumentData.insert(std::pair<std::string, std::string>(s1, s2));
		}
		else
		{
			instrumentData.insert(std::pair<std::string, std::string>(s1, s2));
		}
	} while (nestingDepth > 0);

	createPatchFromData(instrumentData).printPatchData();
}

void PatchFileParser::parseFile(std::ifstream& file)
{
	std::string s1, s2, line;

	
}

//------------------------------- PUBLIC --------------------------------//

std::vector<Patch> PatchFileParser::loadPatchData(std::string filename)
{/*
	std::ifstream patchFileStream(filename);

	if (!patchFileStream.is_open())
	{
		std::cout << "FILE NOT OPEN!\n";
	}

	parseHeader(patchFileStream);
	parseInstruments(patchFileStream);
	*/
	strToIntVector("100,95,23,42");

	std::vector<Patch> v;
	return v;
}