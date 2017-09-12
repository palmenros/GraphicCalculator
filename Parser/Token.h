#pragma once
#include <string>
#include <vector>
#include <map>

enum class TokenType
{
	Operator,
	Number,
	OpenParenthesis,
	CloseParenthesis,
	FunctionCall,
	FunctionSeparator,
	Variable
};

enum class TokenAssociativity
{
	RightToLeft,
	LeftToRight
};

struct Operator
{
	TokenAssociativity associativity;
	int precedence;

	Operator(TokenAssociativity associativity, int precedence)
		: associativity(associativity), precedence(precedence)
	{	
	}

	Operator() = default;

};

class Token
{
protected:

	static std::map<char, Operator> operators;


	float numberRepresentation;
	std::string str;

	int position;
	TokenType type;
	Operator op;

	void setTokenType(const std::string& str);

public:
	
	Token(const std::string& token, int position = -1);

	TokenType getType() const;
	std::string getString() const;

	Operator getOperator() const;
	float getNumericalRepresentation() const;
	int getPosition() const;
};
