#include "Interpreter.h"
#include "FunctionTable.h"
#include <stack>
#include "Utils/StackUtils.h"

Number Interpreter::calculate(const std::vector<Token>& tokens, const SymbolTable& symbolTable)
{
	std::stack<Number> s;
	for (const Token& tk : tokens)
	{
		if (tk.getType() == TokenType::Number)
		{
			s.push(tk.getNumericalRepresentation());
			continue;
		}

		if (tk.getType() == TokenType::FunctionCall)
		{
			InterpreterFunction f = FunctionTable::getFunction(tk.getString());
			std::vector<Number> params;
			for (int i = 0; i < f.parameterNumber; i++)
			{
				params.push_back(StackUtils<Number>::safePop(s, tk, "Invalid parameter count of function : " + tk.getString()));
			}
			s.push(f(params));
			continue;
		}

		if (tk.getType() == TokenType::Operator)
		{
			if (tk.getString() == "#")
			{
				Number a = StackUtils<Number>::safePop(s, tk, "Invalid use of operator #");
				s.push(Number(0) - a);
			}
			else
			{
				Number b = StackUtils<Number>::safePop(s, tk, "Invalid use of operator " + tk.getString());
				Number a = StackUtils<Number>::safePop(s, tk, "Invalid use of operator " + tk.getString());

				Number res;
				switch(tk.getString()[0])
				{
				case '+':
					res = a + b;
					break;
				case '-':
					res = a - b;
					break;
				case '/':
					res = a / b;
					break;
				case '*':
					res = a * b;
					break;
				case '^':
					res = a.power(b);
					break;
				default:
					throw ParseException("Unknown operator " + tk.getString());
				}

				s.push(res);
			}
			continue;
		}

		if(tk.getType() == TokenType::Variable)
		{
			s.push(symbolTable.resolve(tk.getString()));
		}


	}

	//If only one token left, output it, if not throw error
	Number result = StackUtils<Number>::safePop(s, Token(""),"Interpreter error");
	if (!s.empty())
	{
		throw ParseException(Token(""), "Interpreter error");
	}
	return result;
}
