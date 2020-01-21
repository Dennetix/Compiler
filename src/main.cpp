#include <iostream>
#include <fstream>

#include "Preprocessor.h"
#include "Lexer.h"
#include "Parser.h"

std::vector<std::string> readFile(const std::string& path)
{
	std::vector<std::string> res;
	std::ifstream file(path);
	if (file.is_open())
	{
		std::string line = "";
		while (getline(file, line))
		{
			res.push_back(line);
		}
	}
	return res;
}

int main() {
	com::Preprocessor preprocessor;
	com::Lexer lexer;
	com::Parser parser;

	std::vector<std::string> file = readFile("res/test.lang");
	std::string code = preprocessor.process(file);
	std::vector<com::Token> tokens = lexer.lex(code);
	parser.parse(tokens);

	auto str = com::tokensToString(tokens);
	for (std::string s : str)
		std::cout << s << std::endl;

	return 0;
}
