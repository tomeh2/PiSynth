#pragma once

#include <vector>
#include <string>
#include <map>

class Patch
{
private:
	//ALGORITHM DATA
	std::string algorithmDescription;
	int operatorCount;
	//OPERATOR DATA
	std::map<int, float> freqRatios;
	std::map<int, float> outputLevels;
	std::map<int, float> modSens;
	//ENVELOPE GENERATOR DATA
	std::map<int, std::vector<int>> expCoeffs;
	std::map<int, std::vector<float>> targetVals;
	std::map<int, std::vector<int>> holdTimes;

public:
	Patch();
	~Patch();

	//--------------------- SETTERS -------------------------//
	//ALGORITHM DATA
	void setAlgDescription(std::string algorithmDescription);
	void setOperatorCount(int operatorCount);
	//OPERATOR DATA
	void setFreqRatio(int operatorID, float freqRatio);
	void setOutputLevel(int operatorID, float outputLevel);
	void setModulationSensitivity(int operatorID, float modulationSensitivity);
	//ENVELOPE GENERATOR DATA
	void addEnvelopeSegment(int operatorID, int speed, float targetVal, int holdTime);

	//-------------------- GETTERS ------------------------//
	//ALGORITHM DATA
	std::string getAlgDescription();
	int getOperatorCount();
	//OPERATOR DATA
	float getFreqRatio(int operatorID);
	float getOutputLevel(int operatorID);
	float getModulationSensitivity(int operatorID);
	//ENVELOPE GENERATOR DATA
	int getEnvSegmentCount(int operatorID);
	std::vector<int> getCoefficients(int operatorID);
	std::vector<float> getTargets(int operatorID);
	std::vector<int> getHoldTimes(int operatorID);

	//DEBUG
	void printPatchData();
};

