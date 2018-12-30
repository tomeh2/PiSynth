#pragma once

#include <vector>
#include <map>

class Patch
{
private:
	//ALGORITHM DATA
	const char* algorithmDescription;
	int operatorCount;
	//OPERATOR DATA
	std::map<int, float> freqRatios;
	std::map<int, float> outputLevels;
	std::map<int, float> modSens;
	//ENVELOPE GENERATOR DATA
	std::map<int, std::vector<float>> expCoeffs;
	std::map<int, std::vector<float>> targetVals;
	std::map<int, std::vector<float>> holdTimes;

public:
	Patch();
	~Patch();

	//--------------------- SETTERS -------------------------//
	//ALGORITHM DATA
	void setAlgDescription(const char* algDescription);
	void setOperatorCount(int operatorCount);
	//OPERATOR DATA
	void setFreqRatio(int operatorID, float freqRatio);
	void setOutputLevel(int operatorID, float outputLevel);
	void setModulationSensitivity(int operatorID, float modulationSensitivity);
	//ENVELOPE GENERATOR DATA
	void addEnvelopeSegment(int operatorID, float expCoeff, float targetVal, float holdTime);

	//-------------------- GETTERS ------------------------//
	//ALGORITHM DATA
	const char* getAlgDescription();
	int getOperatorCount();
	//OPERATOR DATA
	float getFreqRatio(int operatorID);
	float getOutputLevel(int operatorID);
	float getModulationSensitivity(int operatorID);
	//ENVELOPE GENERATOR DATA
	int getEnvSegmentCount();
	std::vector<float> getCoefficients(int operatorID);
	std::vector<float> getTargets(int operatorID);
	std::vector<float> getHoldTimes(int operatorID);

	//DEBUG
	void printPatchData();
};

