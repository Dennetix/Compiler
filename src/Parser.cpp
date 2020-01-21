#include "Parser.h"

#include <iterator>

namespace com {

    void Parser::parse(const std::vector<Token>& _tokens)
    {
        this->_tokens = _tokens;
        _currentToken = this->_tokens.begin();

        while (_parseStatement()) { }
    }

    void Parser::_nextToken()
    {
        if (_currentToken != _tokens.end())
            _currentToken++;
    }

    bool Parser::_parseStatement()
    {
        if (_currentToken->first == TokenType::OPEN_CURLY_BRACKET)



        return false;
    }

}
