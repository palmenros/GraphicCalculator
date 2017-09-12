#include "Double.h"


Double::Double(double d)
	: d(d)
{
}

bool Double::isNegative() const
{
	return i < 0;
}

bool almostEqualDouble(double a, double b, double maxDiff, uint64_t maxUlpsDiff)
{
	double absDiff = abs(a - b);
	if(absDiff < maxDiff)
	{
		return true;
	}

	Double uA(a);
	Double uB(b);

	if(uA.isNegative() != uB.isNegative())
	{
		return false;
	}

	uint64_t ulpsDiff = abs(uA.i - uB.i);

	if(ulpsDiff < maxUlpsDiff)
	{
		return true;
	}

	return false;
}