#pragma once

#include <vector>

#include "utils/Token.h"

namespace com {

    class Parser
    {
    public:
        void parse(const std::vector<Token>& tokens);

    private:
        void _nextToken();

        int _parseStatement();

    private:
        std::vector<Token> _tokens;
        std::vector<Token>::iterator _currentToken;
    };

}
