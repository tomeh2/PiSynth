#pragma once

/**
A block header allows us to build complex structures out of Operators
*/
class Block
{
public:
	virtual ~Block() {}
	virtual float getNextSample(float input) = 0;
};