#pragma once
#include <cstdint>
#include <limits>

struct Double
{
	union
	{
		double d;
		int64_t i;
	};

	bool isNegative() const;

	Double(double d);
};

bool almostEqualDouble(double a, double b, double maxDiff = DBL_EPSILON, uint64_t maxUlpsDiff = 1);