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

	std::cout << " -------------------  INPUT  -------------------" << std::endl;
	std::vector<std::string> file = readFile("res/test.lang");
	for (std::string s : file)
		std::cout << s << std::endl;

	std::cout << "\n ----------------  PREPROCESSOR  ---------------" << std::endl;
	std::string code = preprocessor.process(file);
	std::cout << code << std::endl;

	std::cout << "\n --------------  LEXICAL ANALYSIS  -------------" << std::endl;
	std::vector<com::Token> tokens = lexer.lex(code);
	for (com::Token t : tokens)
		std::cout << com::tokenToString(t) << std::endl;

	std::cout << "\n --------------  SYNTAX ANALYSIS  --------------" << std::endl;
	com::Program tree = parser.parse(tokens);
	tree.print();

	return 0;
}
