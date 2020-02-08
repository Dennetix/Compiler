#pragma once

#include <vector>

#include "../utils/Token.h"

namespace com {

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
