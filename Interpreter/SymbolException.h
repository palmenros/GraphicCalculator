#pragma once

#include <exception>
#include <string>

class SymbolException : public std::exception
{

protected:

	std::string symbol;

public:
	
	SymbolException(const std::string& symbol);

};
