#include <iostream>
#include <fstream>

#include "Preprocessor.h"
#include "Lexer.h"
#include "Parser.h"
#include "CodeGenerator.h"

std::vector<std::string> readInput(const std::string& path)
{
	std::vector<std::string> res;
	std::ifstream file(path);
	if (file.is_open())
	{
		std::string line = "";
		while (getline(file, line))
			res.push_back(line);
	}
	return res;
}

void writeOutput(const std::string& path, const std::string& str)
{
	std::ofstream file(path);
	if (file.is_open())
		file << str;
}

int main() {
	com::Preprocessor preprocessor;
	com::Lexer lexer;
	com::Parser parser;
	com::CodeGenerator codegen;

	std::cout << " -------------------  INPUT  -------------------" << std::endl;
	std::vector<std::string> input = readInput("res/test.lang");
	for (std::string s : input)
		std::cout << s << std::endl;

	std::cout << "\n ----------------  PREPROCESSOR  ---------------" << std::endl;
	std::string code = preprocessor.process(input);
	std::cout << code << std::endl;

	std::cout << "\n --------------  LEXICAL ANALYSIS  -------------" << std::endl;
	std::vector<com::Token> tokens = lexer.lex(code);
	for (com::Token t : tokens)
		std::cout << com::tokenToString(t) << std::endl;

	std::cout << "\n --------------  SYNTAX ANALYSIS  --------------" << std::endl;
	com::Program tree = parser.parse(tokens);
	tree.print();

	std::cout << "\n --------------  CODE GENERATION  --------------" << std::endl;
	std::string output = codegen.generate(tree);
	std::cout << output;

	writeOutput("res/output.s", output);

	return 0;
}
