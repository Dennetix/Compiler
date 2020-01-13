#include <iostream>
#include <fstream>

#include "Preprocessor.h"
#include "Lexer.h"

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

	std::vector<std::string> file = readFile("res/test.lang");
	std::string code = preprocessor.process(file);
	std::vector<std::pair<com::TokenType, std::string>> tokens = lexer.lex(code);

	for (auto p : tokens)
		std::cout << static_cast<std::underlying_type<com::TokenType>::type>(p.first) << "\t" << p.second << std::endl;

	return 0;
}
