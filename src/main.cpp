#include <iostream>
#include <fstream>

#include "utils/ErrorHandler.h"

#include "compiler/Preprocessor.h"
#include "compiler/Lexer.h"
#include "compiler/Parser.h"
#include "compiler/SemanticAnalyser.h"
#include "compiler/CodeGenerator.h"

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
	else
	{
		com::ErrorHandler::addError("Failed to open input file '" + path + "'", true);
	}
	return res;
}

void writeOutput(const std::string& path, const std::string& str)
{
	std::ofstream file(path);
	if (file.is_open())
		file << str;
	else
		com::ErrorHandler::addError("Failed to open output file '" + path + "'", true);
}

int main(int argc, char** argv)
{
	std::string inPath;
	std::string outPath = "output.s";
	if (argc > 1)
	{
		inPath = argv[1];
		if (argc > 2)
			outPath = argv[2];
		else
			com::ErrorHandler::addError("No output file specified, using '" + outPath + "'");
	}
	else
	{
		com::ErrorHandler::addError("No input file specified", true);
	}

	if (com::ErrorHandler::printErrors())
		return 1;

	com::Preprocessor preprocessor;
	com::Lexer lexer;
	com::Parser parser;
	com::SemanticAnalyser semanticAnalyser;
	com::CodeGenerator codeGenerator;

	std::cout << " -------------------  INPUT  -------------------" << std::endl;
	std::vector<std::string> input = readInput(inPath);
	if (com::ErrorHandler::printErrors())
		return 1;
	for (std::string s : input)
		std::cout << s << std::endl;

	std::cout << "\n ----------------  PREPROCESSOR  ---------------" << std::endl;
	std::string code = preprocessor.process(input);
	std::cout << code << std::endl;

	std::cout << "\n --------------  LEXICAL ANALYSIS  -------------" << std::endl;
	std::vector<com::Token> tokens = lexer.lex(code);
	if (com::ErrorHandler::printErrors())
		return 1;
	for (com::Token t : tokens)
		std::cout << com::tokenToString(t) << std::endl;

	std::cout << "\n --------------  SYNTAX ANALYSIS  --------------" << std::endl;
	com::Program tree = parser.parse(tokens);
	if (com::ErrorHandler::printErrors())
		return 1;
	tree.print();

	std::cout << "\n -------------  SEMANTIC ANALYSIS  -------------" << std::endl;
	std::vector<std::string> symbols = semanticAnalyser.analyse(tree);
	if (com::ErrorHandler::printErrors())
		return 1;
	for (std::string s : symbols)
		std::cout << s << std::endl;

	std::cout << "\n --------------  CODE GENERATION  --------------" << std::endl;
	std::string output = codeGenerator.generate(tree, symbols);
	std::cout << output;

	std::cout << "\n -------------------  OUTPUT  ------------------" << std::endl;
	writeOutput(outPath, output);
	if (com::ErrorHandler::printErrors())
		return 1;
	std::cout << "Written output to '" << outPath << "'" << std::endl;



	return 0;
}
