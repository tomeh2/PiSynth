#include "FastMath.h"

float FastMath::expo(float val)
{
	val = 1.f + val / 256.f;
	val *= val;
	val *= val;
	val *= val;
	val *= val;
	val *= val;
	val *= val;
	val *= val;
	val *= val;
	return val;
}