#include "Token.h"
#include "Parser.h"
#include <algorithm>
#include "Interpreter/FunctionTable.h"

std::map<char, Operator> Token::operators
{
	{ '+', Operator(TokenAssociativity::LeftToRight, 2) },
	{ '-', Operator(TokenAssociativity::LeftToRight, 2) },
	{ '*', Operator(TokenAssociativity::LeftToRight, 3) },
	{ '/', Operator(TokenAssociativity::LeftToRight, 3) },
	{ '^', Operator(TokenAssociativity::RightToLeft, 4) },
	{ '#', Operator(TokenAssociativity::RightToLeft, 4) }
};


void Token::setTokenType(const std::string& str)
{

	if(str == "")
	{
		type = TokenType::Variable;
		return;
	}

	char* endPtr;
	float number = strtof(str.c_str(), &endPtr);

	if (endPtr == str.c_str() + str.size())
	{
		//Is a number
		numberRepresentation = number;
		type = TokenType::Number;
		return;
	}

	if(str == "(")
	{
		type = TokenType::OpenParenthesis;
		return;
	}

	if(str == ")")
	{
		type = TokenType::CloseParenthesis;
		return;
	}

	if(str == ",")
	{
		type = TokenType::FunctionSeparator;
		return;;
	}

	if(FunctionTable::functionExists(str))
	{
		type = TokenType::FunctionCall;
		return;
	}

	if(std::find(Parser::operatorList.begin(), Parser::operatorList.end(), str) != Parser::operatorList.end())
	{
		op = operators[str[0]];
		type = TokenType::Operator;
		return;
	}

	type = TokenType::Variable;

}

Token::Token(const std::string& token, int position)
	: str(token), position(position)
{
	setTokenType(str);
}

TokenType Token::getType() const
{
	return type;
}

std::string Token::getString() const
{
	return str;
}

Operator Token::getOperator() const
{
	return op;
}

float Token::getNumericalRepresentation() const
{
	return numberRepresentation;
}

int Token::getPosition() const
{
	return position;
}
