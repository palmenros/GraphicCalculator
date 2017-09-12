#include "SymbolException.h"

SymbolException::SymbolException(const std::string& symbol)
	: exception(symbol.c_str()), symbol(symbol)
{
}
