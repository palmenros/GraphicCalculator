#pragma once

#include <stack>
#include "Parser/ParseException.h"
#include "Parser/Token.h"

template <class T, class E = ParseException>
class StackUtils
{

protected:

	static void throwError(const Token& tk, const std::string& msg)
	{
		if (msg != "")
		{
			throw E(tk, msg);
		}
		else
		{
			throw E(tk);
		}
	}

public:

	static T safeTop(const std::stack<T>& s, const Token& tk, const std::string& msg = "")
	{
		if (s.empty())
		{
			throwError(tk, msg);
		}
		return s.top();
	}

	static T safePop(std::stack<T>& s, const Token& tk, const std::string& msg = "")
	{
		if (s.empty())
		{
			throwError(tk, msg);
		}
		T ret = s.top();
		s.pop();
		return ret;
	}
};
