#pragma once

#include <cstdint>
#include <float.h>

struct Float
{
	
	union 
	{
		float f;
		int32_t i;
	};

	bool isNegative() const;

	Float(float f);

};

bool almostEqualFloat(float a, float b, float maxDiff = FLT_EPSILON, uint32_t maxUlpsDiff = 1);