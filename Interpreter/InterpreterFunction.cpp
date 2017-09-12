#include "InterpreterFunction.h"

InterpreterFunction::InterpreterFunction()
	: parameterNumber(0), function(nullptr)
{
}

InterpreterFunction::InterpreterFunction(const std::function<Number(const std::vector<Number>&)>& f, int parameterNumber)
	: parameterNumber(parameterNumber), function(f)
{
}

Number InterpreterFunction::operator()(const std::vector<Number>& args) const
{
	return function(args);
}
