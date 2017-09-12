#pragma once
#include <map>
#include <string>
#include "InterpreterFunction.h"

#define DEFINE_FUNCTION_MAP(NAME, PARAMETER_COUNT) {#NAME, InterpreterFunction(static_cast<Number(*)(const std::vector<Number>&)>(FunctionTable::NAME), PARAMETER_COUNT)}
#define DEFINE_ONE_PARAM(NAME) \
	static Number NAME(const std::vector<Number>& args){ return NAME(args[0]); } \
	static Number NAME(const Number&);

#define DEFINE_TWO_PARAMS(NAME) \
	static Number NAME(const std::vector<Number>& args) { return NAME(args[0], args[1]); }; \
	static Number NAME(const Number&, const Number&);


class FunctionTable
{
protected:
	static std::map<std::string, InterpreterFunction> functionTable;
public:

	static bool functionExists(const std::string& functionName);

	DEFINE_ONE_PARAM(sin)
	DEFINE_ONE_PARAM(cos)
	DEFINE_ONE_PARAM(sqrt)
	DEFINE_TWO_PARAMS(max)
	DEFINE_TWO_PARAMS(min)

	static InterpreterFunction getFunction(const std::string& name);
};
