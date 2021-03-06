#pragma once

#include <utility>
#include <string>

namespace com {

    enum class TokenType
	{
		NONE,

		SYMBOL,
		NUMBER,

		KEY_IF,
		KEY_WHILE,
		KEY_OUT,

		OP_ADD,
		OP_SUB,
		OP_MUL,
		OP_DIV,
		OP_MUD,
		OP_EQUALS,
		OP_LESS_THAN,
		OP_GREATER_THAN,
		OP_ASSIGN,

		LOP_NOT,
		LOP_AND,
		LOP_OR,

		OPEN_BRACKET,
		CLOSE_BRACKET,
		OPEN_CURLY_BRACKET,
		CLOSE_CURLY_BRACKET,
		SEMICOLON,

        EOI
	};

    using Token = std::pair<TokenType, std::string>;

	std::string tokenTypeToString(TokenType type);
    std::string tokenToString(const Token& token);

}
