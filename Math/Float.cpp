#include "Float.h"
#include <cmath>

bool Float::isNegative() const
{
	return i < 0;
}

Float::Float(float f)
	: f(f)
{
}

bool almostEqualFloat(float a, float b, float maxDiff, uint32_t maxUlpsDiff)
{
	float absDiff = fabs(a - b);
	if(absDiff < maxDiff)
	{
		return true;
	}

	Float uA(a);
	Float uB(b);
	
	if(uA.isNegative() != uB.isNegative())
	{
		return false;
	}

	uint32_t ulpsDiff = abs(uA.i - uB.i);

	if(ulpsDiff < maxUlpsDiff)
	{
		return true;
	}
	return false;
}
