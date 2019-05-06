#include "Patch.h"

#include <iostream>

Patch::Patch()
{
}

Patch::~Patch()
{
}

void Patch::setAlgDescription(std::string algorithmDescription)
{
	this->algorithmDescription = algorithmDescription;
}

void Patch::setOperatorCount(int operatorCount)
{
	this->operatorCount = operatorCount;
}

void Patch::setFreqRatio(int operatorID, float freqRatio)
{
	this->freqRatios[operatorID] = freqRatio;
}

void Patch::setOutputLevel(int operatorID, float outputLevel)
{
	this->outputLevels[operatorID] = outputLevel;
}

void Patch::setModulationSensitivity(int operatorID, float modulationSensitivity)
{
	this->modSens[operatorID] = modulationSensitivity;
}

void Patch::setModSensitivityScalingLimits(int operatorID, float lowerLimit, float upperLimit)
{
	this->modSensScalingLimits[operatorID].push_back(lowerLimit);
	this->modSensScalingLimits[operatorID].push_back(upperLimit);
}

void Patch::addEnvelopeSegment(int operatorID, float speed, float targetVal, float holdTime)
{
	this->expCoeffs[operatorID].push_back(speed);
	this->targetVals[operatorID].push_back(targetVal);
	this->holdTimes[operatorID].push_back(holdTime);
}
//------------------------------- GETTERS ---------------------------//
std::string Patch::getAlgDescription()
{
	return this->algorithmDescription;
}

int Patch::getOperatorCount()
{
	return this->operatorCount;
}

float Patch::getFreqRatio(int operatorID)
{
	return this->freqRatios[operatorID];
}

float Patch::getOutputLevel(int operatorID)
{
	return this->outputLevels[operatorID];
}

float Patch::getModulationSensitivity(int operatorID)
{
	return this->modSens[operatorID];
}

float Patch::getModSensitivityScalingLowLimit(int operatorID)
{
	return this->modSensScalingLimits[operatorID][0];
}

float Patch::getModSensitivityScalingUpLimit(int operatorID)
{
	return this->modSensScalingLimits[operatorID][1];
}

int Patch::getEnvSegmentCount(int operatorID)
{
	return this->expCoeffs[operatorID].size();
}

std::vector<float> Patch::getCoefficients(int operatorID)
{
	return this->expCoeffs[operatorID];
}

std::vector<float> Patch::getTargets(int operatorID)
{
	return this->targetVals[operatorID];
}

std::vector<float> Patch::getHoldTimes(int operatorID)
{
	return this->holdTimes[operatorID];
}

void Patch::printPatchData()
{
	std::cout << "Algorithm: " << this->algorithmDescription << "\n";
	std::cout << "Operator Count: " << this->operatorCount << "\n";
	std::cout << "-----------------------\n";

	for (int i = 0; i < this->operatorCount; i++)
	{
		std::cout << "------------ OPERATOR " << i << " ------------\n";
		std::cout << "Frequency Ratio: " << this->freqRatios[i] << "\n";
		std::cout << "Output Level: " << this->outputLevels[i] << "\n";
		std::cout << "Modulation Sensitivity: " << this->modSens[i] << "\n";
		std::cout << "Mod. Sensitivity Scaling Low | High: " << this->modSensScalingLimits[i][0] << " | " << this->modSensScalingLimits[i][1] << "\n";

		std::cout << "Exponential Coefficients: ";
		for (int j = 0; j < this->expCoeffs[i].size(); j++)
			std::cout << this->expCoeffs[i][j] << " | ";
		std::cout << "\n";

		std::cout << "Target Values           : ";
		for (int j = 0; j < this->targetVals[i].size(); j++)
			std::cout << this->targetVals[i][j] << " | ";
		std::cout << "\n";

		std::cout << "Hold Times              : ";
		for (int j = 0; j < this->holdTimes[i].size(); j++)
			std::cout << this->holdTimes[i][j] << " | ";
		std::cout << "\n";
	}
}