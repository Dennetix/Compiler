#pragma once

#include <vector>
#include <string>
#include <utility>

namespace com {

	enum class TokenType
	{
		NONE = 0,

		SYMBOL = 1,
		NUMBER = 2,
		STRING = 3,

		KEY_IF = 4,
		KEY_WHILE = 5,
		KEY_RETURN = 6,

		OP_ASSIGN = 7,
		OP_ADD = 8,
		OP_SUB = 9,
		OP_MUL = 10,
		OP_DIV = 11,
		OP_EQUALS = 12,
		OP_LESS_THAN = 13,
		OP_GREATER_THAN = 14,

		LOP_NOT = 15,
		LOP_AND = 16,
		LOP_OR = 17,

		OPEN_BRACKET = 18,
		CLOSE_BRACKET = 19,
		OPEN_CURLY_BRACKET = 20,
		CLOSE_CURLY_BRACKET = 21,
		COMMA = 22,
		SEMICOLON = 23
	};

	using Token = std::pair<TokenType, std::string>;

	class Lexer
	{
	public:
		std::vector<Token> lex(const std::string& file);

	private:
		void _push(const Token& token);
		void _pushCurrentToken();

	private:
		std::string _file;

		std::vector<Token> _tokens;
		Token _currentToken;
	};

}
