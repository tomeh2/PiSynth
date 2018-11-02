#pragma once

#include "Algorithm.h"

class Voice
{
private:
	Algorithm* algorithm;
public:
	Voice(Algorithm* algorithm);
	~Voice();

	float getNextSample();
	void keyDown(int keyNum);
	void keyUp();
};

