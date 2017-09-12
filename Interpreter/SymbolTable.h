#pragma once

#include <map>
#include "Math/Number.h"

class SymbolTable
{
protected:
	
	static const std::map<std::string, Number> constants;
	std::map<std::string, Number> symbols;

public:

	void add(const std::string& name, const Number& value);

	Number resolve(const std::string& name) const;
};
