#include <iostream>
#include <string>
#include "Parser/Parser.h"
#include "Parser/Token.h"
#include "Math/Double.h"
#include "Interpreter/Interpreter.h"

using namespace std;

void printVector(const vector<Token>& tokens)
{
	for (const Token& t : tokens)
	{
		cout << t.getString() << " ";
	}
	cout << endl;
}

//TODO: GRAPH IT
//TODO: SIMPLIFY EXPRESSIONS

int main()
{
	string line;

	while (getline(cin, line))
	{
		Parser parser(line);
		SymbolTable table;
		Number result = Interpreter::calculate(parser.parse(), table);
		
		cout << result << endl;
	}

	cin.get();
	return 0;
}
