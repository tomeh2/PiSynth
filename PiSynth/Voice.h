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

	/**
	Activates the voice with the given key number. The voice will
	calculate the frequency from the given key number and set the
	operators to the right frequency.

	@param keyNum -> key number from 1 - 88
	*/
	void keyDown(int keyNum);

	/**
	Starts the release part of the envelope and will put the voice
	in inactive state once the envelople goes idle. For now it just
	sets the voice's volume to 0.
	*/
	void keyUp();

	/**
	Returns true or false depending on whether the voice is active
	(the envelope generator is not idle) or not (the envelope is
	idle).

	@returns -> true or false
	*/
	bool isActive();
};

