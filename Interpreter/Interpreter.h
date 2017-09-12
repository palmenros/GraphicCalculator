#pragma once
#include <vector>
#include "Parser/Token.h"
#include "Math/Number.h"
#include "SymbolTable.h"

class Interpreter
{

public:

	static Number calculate(const std::vector<Token>& tokens, const SymbolTable& symbolTable);
	
};
