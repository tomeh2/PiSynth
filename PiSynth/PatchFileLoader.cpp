#include "PatchFileLoader.h"
#include "Patch.h"
#include "StringHelper.h"
#include "Logger.h"

#include <iostream>
#include <sstream>
#include <map>

#define MAX_LINE_LEN 128

//------------------------------- PRIVATE -------------------------------//
Patch PatchFileLoader::createPatchFromData(std::map<std::string, std::string> patchData)
{
	Patch p;

	p.setOperatorCount(std::stoi(patchData["opv"]));
	p.setAlgDescription(patchData["alg"]);

	for (int i = 0; i < p.getOperatorCount(); i++)
	{
		p.setFreqRatio(i, std::stof(patchData[std::string("freq_ratio") + std::to_string(i)]));
		p.setOutputLevel(i, std::stof(patchData[std::string("out_lvl") + std::to_string(i)]));

		std::vector<float> scalingLimits = StringHelper::strToFloatVector(patchData[std::string("mod_sens_range") + std::to_string(i)], '-');
		p.setModSensitivityScalingLimits(i, scalingLimits[0], scalingLimits[1]);

		std::vector<float> envelopeRates = StringHelper::strToFloatVector(patchData[std::string("env_rate") + std::to_string(i)], ',');
		std::vector<float> envelopeLevels = StringHelper::strToFloatVector(patchData[std::string("env_lvl") + std::to_string(i)], ',');
		std::vector<float> holdTimes = StringHelper::strToFloatVector(patchData[std::string("hold_time") + std::to_string(i)], ',');
		for (int j = 0; j < envelopeRates.size(); j++)
		{
			p.addEnvelopeSegment(i, envelopeRates[j], envelopeLevels[j], holdTimes[j]);
		}
	}
	return p;
}

std::string PatchFileLoader::getLine(std::ifstream& file)
{
	char str[MAX_LINE_LEN];
	file.getline(str, MAX_LINE_LEN);
	return std::string(str);
}

void PatchFileLoader::parseHeader(std::ifstream& file)
{
	std::string s1, s2, line;

	do
	{
		line = getLine(file);
		
		if (line.find("end_prop") != std::string::npos)
			break;
		else
		{
			StringHelper::splitLine(line, '=', s1, s2);
		}
	} while (!file.eof());
}

Patch PatchFileLoader::parseInstrument(std::ifstream& file)
{
	std::map<std::string, std::string> instrumentData;
	std::string s1, s2, line;
	int operatorNum = -1, nestingDepth = 1;

	do
	{
		line = getLine(file);

		if (line.find("{") != std::string::npos)
		{
			nestingDepth++;
			if (nestingDepth > 1)
				operatorNum++;
			continue;
		}
		else if (line.find("}") != std::string::npos)
		{
			nestingDepth--;
			continue;
		}
		else if (line == "")
			continue;

		StringHelper::splitLine(line, '=', s1, s2);
		s1 = StringHelper::removeWhitespace(s1);

		if (operatorNum >= 0 && nestingDepth > 1)
		{
			s1.append(std::to_string(operatorNum));
			instrumentData.insert(std::pair<std::string, std::string>(s1, s2));
		}
		else
		{
			instrumentData.insert(std::pair<std::string, std::string>(s1, s2));
		}
	} while (nestingDepth > 0);
	
	return createPatchFromData(instrumentData);
}

std::vector<Patch> PatchFileLoader::parseFile(std::ifstream& file)
{
	std::vector<Patch> patches;

	int loadedPatches = 0;
	while (!file.eof())
	{
		std::string line = getLine(file);

		if (line.find("{") != std::string::npos)
		{
			patches.push_back(parseInstrument(file));
			loadedPatches++;
		}
		else if (line.find("end_file") != std::string::npos)
			break;
	}

	return patches;
}

//------------------------------- PUBLIC --------------------------------//

std::vector<Patch> PatchFileLoader::loadPatchData(std::string filename)
{
	std::ifstream patchFileStream(filename);
	std::vector<Patch> loadedPatches;

	if (!patchFileStream.is_open())
	{
		Logger::print("Could not open the file. Filename: " + filename);
	}
	else
	{
		parseHeader(patchFileStream);
		loadedPatches = parseFile(patchFileStream);

		Logger::print("Loaded " + std::to_string(loadedPatches.size()) + " patches");
	}

	return loadedPatches;
}