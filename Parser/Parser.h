#pragma once
#include <string>
#include <vector>
#include "Token.h"
#include <stack>

class Parser
{
private:

	std::string source;

protected:

	static std::vector<Token> tokenize(const std::string& str);

	static std::vector<Token> infixToPostfix(const std::vector<Token>& tokens);
	static void preprocess(std::vector<Token>& tokens);

public:

	static std::vector<std::string> operatorList;

	Parser(const std::string& source);
	std::vector<Token> parse() const;
};
