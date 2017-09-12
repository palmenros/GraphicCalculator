#include "SymbolTable.h"
#include "SymbolException.h"

#define M_PI       3.14159265358979323846   // pi
#define M_E        2.71828182845904523536   // e

const std::map<std::string, Number> SymbolTable::constants =
{
	{ "pi", M_PI },
	{ "i", Number(0, 1) },
	{ "e", M_E }
};

void SymbolTable::add(const std::string& name, const Number& value)
{
	symbols[name] = value;
}

Number SymbolTable::resolve(const std::string& name) const
{
	std::map<std::string, Number>::const_iterator cit = constants.find(name);
	if (cit != constants.end())
	{
		return cit->second;
	}
	
	std::map<std::string, Number>::const_iterator it = symbols.find(name);
	if(it != symbols.end())
	{
		return it->second;
	}

	throw SymbolException(name);

}
