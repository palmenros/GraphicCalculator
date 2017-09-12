#pragma once
#include <exception>
#include <string>
#include "Token.h"

class ParseException : public std::exception
{
protected:

	Token tk;

public:
	ParseException(const Token& tk, const std::string msg = "There are unbalanced parenthesis");
};
