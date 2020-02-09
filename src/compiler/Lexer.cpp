#include "Lexer.h"

#include <regex>

#include "../utils/ErrorHandler.h"

namespace com {

	std::vector<Token> Lexer::lex(const std::string& file)
	{
		_tokens = { };
		_currentToken = { TokenType::NONE, "" };

		for (char c : file)
		{
			if (std::string("+-*/%<>!&|(){};").find(c) != std::string::npos)
			{
				_pushCurrentToken();
				if (c == '+')
					_tokens.push_back({ TokenType::OP_ADD, "" });
				else if (c == '-')
					_tokens.push_back({ TokenType::OP_SUB, "" });
				else if (c == '*')
					_tokens.push_back({ TokenType::OP_MUL, "" });
				else if (c == '/')
					_tokens.push_back({ TokenType::OP_DIV, "" });
				else if (c == '%')
					_tokens.push_back({ TokenType::OP_MUD, "" });
				else if (c == '<')
					_tokens.push_back({ TokenType::OP_LESS_THAN, "" });
				else if (c == '>')
					_tokens.push_back({ TokenType::OP_GREATER_THAN, "" });
				else if (c == '!')
					_tokens.push_back({ TokenType::LOP_NOT, "" });
				else if (c == '&')
					_tokens.push_back({ TokenType::LOP_AND, "" });
				else if (c == '|')
					_tokens.push_back({ TokenType::LOP_OR, "" });
				else if (c == '(')
					_tokens.push_back({ TokenType::OPEN_BRACKET, "" });
				else if (c == ')')
					_tokens.push_back({ TokenType::CLOSE_BRACKET, "" });
				else if (c == '{')
					_tokens.push_back({ TokenType::OPEN_CURLY_BRACKET, "" });
				else if (c == '}')
					_tokens.push_back({ TokenType::CLOSE_CURLY_BRACKET, "" });
				else if (c == ';')
					_tokens.push_back({ TokenType::SEMICOLON, "" });
			}
			else if (c == '=')
			{
				if (_currentToken.first == TokenType::OP_ASSIGN)
				{
					_push({ TokenType::OP_EQUALS, "" });
				}
				else
				{
					_pushCurrentToken();
					_currentToken = { TokenType::OP_ASSIGN, "" };
				}
			}
			else if (std::regex_match(std::string(1, c), std::regex("[a-zA-Z]")))
			{
				if (_currentToken.first != TokenType::SYMBOL)
					_pushCurrentToken();

				_currentToken.first = TokenType::SYMBOL;
				_currentToken.second += c;

				if (_currentToken.second == "if")
					_push({ TokenType::KEY_IF, "" });
				else if (_currentToken.second == "while")
					_push({ TokenType::KEY_WHILE, "" });
				else if (_currentToken.second == "out")
					_push({ TokenType::KEY_OUT, "" });
			}
			else if (std::regex_match(std::string(1, c), std::regex("[0-9]")))
			{
				if (_currentToken.first == TokenType::NUMBER || _currentToken.first == TokenType::SYMBOL)
				{
					_currentToken.second += c;
				}
				else
				{
					_pushCurrentToken();
					_currentToken = { TokenType::NUMBER, std::string(1, c) };
				}
			}
			else
			{
				ErrorHandler::addError("Lexing error: unexpected character '" + std::string(1, c) + "'");
			}
		}

		_pushCurrentToken();
		_push({ TokenType::EOI, "" });

		return _tokens;
	}

	void Lexer::_push(const Token& token)
	{
		_tokens.push_back(token);
		_currentToken = { TokenType::NONE, "" };
	}

	void Lexer::_pushCurrentToken()
	{
		if (_currentToken.first != TokenType::NONE)
			_push(_currentToken);
	}

}
