#pragma once
#include <functional>
#include "Math/Number.h"
#include <vector>

struct InterpreterFunction
{
	int parameterNumber;
	std::function<Number(const std::vector<Number>&)> function;

	InterpreterFunction();
	InterpreterFunction(const std::function<Number(const std::vector<Number>&)>& f, int parameterNumber);

	Number operator()(const std::vector<Number>& args) const;
};
