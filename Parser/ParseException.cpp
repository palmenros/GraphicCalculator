#include "ParseException.h"

ParseException::ParseException(const Token& tk, const std::string msg)
	: std::exception(msg.c_str()), tk(tk)
{
}
