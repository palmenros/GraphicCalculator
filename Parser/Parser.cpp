#include "Parser.h"
#include "ParseException.h"
#include <cctype>
#include <stack>
#include "Utils/StackUtils.h"

std::vector<std::string> Parser::operatorList =
{
	"+",
	"-",
	"*",
	"/",
	"^",
	"#"
};

Parser::Parser(const std::string& source)
	: source(source)
{
}

std::vector<Token> Parser::parse() const
{
	std::vector<Token> tokens = tokenize(source);
	preprocess(tokens);
	return infixToPostfix(tokens);
}

std::vector<Token> Parser::tokenize(const std::string& str)
{
	std::vector<Token> result;

	std::string tmp;

	int position = 0;
	int tokenPosition = 0;

	for (char c : str)
	{
		position++;

		if (std::isspace(c))
		{
			if (tmp != "")
			{
				result.push_back(Token(tmp, tokenPosition));
				tmp = "";
			}
			continue;
		}

		std::string s(1, c);
		bool shouldBreak = c == '(' || c == ')' || c == ',' ||
			std::find(operatorList.begin(), operatorList.end(), s) != operatorList.end();

		if (shouldBreak)
		{
			if (tmp != "")
			{
				result.push_back(Token(tmp, tokenPosition));
				tmp = "";
			}

			result.push_back(Token(s, position));
		}
		else
		{
			if(tmp == "")
			{
				tokenPosition = position;
			}
			tmp.push_back(c);
		}

	}

	if (tmp != "")
	{
		result.push_back(Token(tmp, tokenPosition));
	}

	return result;
}

std::vector<Token> Parser::infixToPostfix(const std::vector<Token>& tokens)
{
	std::vector<Token> result;
	std::stack<Token> stack;

	for (const Token& tk : tokens)
	{
		TokenType type = tk.getType();
		if (type == TokenType::Number || type == TokenType::Variable)
		{
			result.push_back(tk);
			continue;
		}

		if (type == TokenType::FunctionCall)
		{
			stack.push(tk);
			continue;
		}

		if (type == TokenType::FunctionSeparator)
		{
			while (StackUtils<Token>::safeTop(stack, tk).getType() != TokenType::OpenParenthesis)
			{
				result.push_back(StackUtils<Token>::safePop(stack, tk));
			}
			continue;
		}

		if (type == TokenType::Operator)
		{
			while (
				!stack.empty() &&
				stack.top().getType() == TokenType::Operator
			)
			{
				Operator o1 = tk.getOperator();
				Operator o2 = stack.top().getOperator();

				if (o1.associativity == TokenAssociativity::LeftToRight &&
					o1.precedence <= o2.precedence)
				{
					result.push_back(StackUtils<Token>::safePop(stack, tk));
				}
				else if (o1.associativity == TokenAssociativity::RightToLeft &&
					o1.precedence < o2.precedence)
				{
					result.push_back(StackUtils<Token>::safePop(stack, tk));
				}
				else
				{
					break;
				}
			}

			stack.push(tk);
			continue;
		}

		if (type == TokenType::OpenParenthesis)
		{
			stack.push(tk);
			continue;
		}

		if (type == TokenType::CloseParenthesis)
		{
			while (StackUtils<Token>::safeTop(stack, tk).getType() != TokenType::OpenParenthesis)
			{
				result.push_back(StackUtils<Token>::safePop(stack, tk));
			}

			stack.pop();

			if (!stack.empty() && stack.top().getType() == TokenType::FunctionCall)
			{
				result.push_back(stack.top());
				stack.pop();
			}
		}
	}

	while (!stack.empty())
	{
		Token tk = StackUtils<Token>::safePop(stack, Token(""));
		if (tk.getType() == TokenType::OpenParenthesis ||
			tk.getType() == TokenType::CloseParenthesis)
		{
			throw ParseException(tk, "There are unbalanced parenthesis");
		}

		result.push_back(tk);
	}

	return result;
}

void Parser::preprocess(std::vector<Token>& tokens)
{
	TokenType lastType = TokenType::Operator;
	bool lastUnaryOperator = false;

	for (std::vector<Token>::iterator it = tokens.begin(); it != tokens.end(); ++it)
	{

		Token& tk = *it;

		//Implement unary minus operator
		if (tk.getString() == "-")
		{
			//If previous token was an operator, substitute this token with Unary Operator
			if (
				(lastType == TokenType::Operator || lastType == TokenType::FunctionSeparator || lastType == TokenType::FunctionCall || lastType == TokenType::OpenParenthesis) && !lastUnaryOperator
				)
			{
				*it = Token("#", it->getPosition());
				lastUnaryOperator = true;
			}
			else
			{
				lastUnaryOperator = false;
			}
		}
		else
		{
			lastUnaryOperator = false;
		}

		//Allow implicit multiplication of parenthesis
		if(tk.getType() == TokenType::OpenParenthesis)
		{
			bool condition = lastType == TokenType::CloseParenthesis ||
							 lastType == TokenType::Number	         ||
							 lastType == TokenType::Variable;

			if(condition)
			{
				//Add multiplication token before this token
				it = tokens.insert(it, Token("*", it->getPosition()));
				++it;
			}

		}

		//Allow implicit multiplication of number and variable
		if (tk.getType() == TokenType::Variable)
		{
			//Let's see if it starts by a number
			const std::string& s = tk.getString();
			char* endPtr = nullptr;
			double val = strtod(s.c_str(), &endPtr);

			if (endPtr != s.c_str())
			{
				//String has a numerical value

				if (*endPtr != 0)
				{
					//There are additional characters

					//Insert numerical token first
					it = tokens.insert(it, Token(std::to_string(val), it->getPosition()));
					++it;

					//Insert multiplication token
					it = tokens.insert(it, Token("*", it->getPosition()));
					++it;

					ptrdiff_t size = endPtr - s.c_str();

					//Change token to only contain rest of the string
					*it = Token(std::string(endPtr), it->getPosition() + size);
				}

			}

		}

		lastType = it->getType();
		
	}
}
