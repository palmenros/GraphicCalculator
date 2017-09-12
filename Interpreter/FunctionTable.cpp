#include "FunctionTable.h"
#include <functional>
#include "Math/Number.h"
#include <cmath>
#include <complex>

std::map<std::string, InterpreterFunction> FunctionTable::functionTable
{
	DEFINE_FUNCTION_MAP(sin,  1),
	DEFINE_FUNCTION_MAP(cos,  1),
	DEFINE_FUNCTION_MAP(sqrt, 1),
	DEFINE_FUNCTION_MAP(max,  2),
	DEFINE_FUNCTION_MAP(min,  2)
};

InterpreterFunction FunctionTable::getFunction(const std::string& name)
{
	return functionTable[name];
}

bool FunctionTable::functionExists(const std::string& functionName)
{
	return functionTable.find(functionName) != functionTable.end();
}

Number FunctionTable::sin(const Number& a)
{
	std::complex<double> r = std::sin(std::complex<double>(a.getReal(), a.getImaginary()));
	return Number(r.real(), r.imag());
}

Number FunctionTable::cos(const Number& a)
{
	std::complex<double> r = std::cos(std::complex<double>(a.getReal(), a.getImaginary()));
	return Number(r.real(), r.imag());
}

Number FunctionTable::max(const Number& a, const Number& b)
{
	return a.getReal() > b.getReal() ? a : b;
}

Number FunctionTable::min(const Number& a, const Number& b)
{
	return a.getReal() < b.getReal() ? a : b;
}

Number FunctionTable::sqrt(const Number& a)
{
	return a.power(0.5);
}
