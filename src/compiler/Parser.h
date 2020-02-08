#pragma once

#include "../utils/Token.h"
#include "../utils/ASTTypes.h"

namespace com {

    class Parser
    {
    public:
        Program parse(const std::vector<Token>& tokens);

    private:
        void _nextToken();
        bool _acceptToken(TokenType type);
        void _expectToken(TokenType type);

        std::vector<std::unique_ptr<Statement>> _parseStatements();
        std::unique_ptr<Statement> _parseStatement();
        std::unique_ptr<Expression> _parseExpression();
        std::unique_ptr<Expression> _parseLogicalOr();
        std::unique_ptr<Expression> _parseLogicalAnd();
        std::unique_ptr<Expression> _parseEquals();
        std::unique_ptr<Expression> _parseLessGreaterThan();
        std::unique_ptr<Expression> _parseSum();
        std::unique_ptr<Expression> _parseProduct();
        std::unique_ptr<Expression> _parseLogicalNot();
        std::unique_ptr<Expression> _parseUnaryMinus();
        std::unique_ptr<Expression> _parseLiteral();

    private:
        std::vector<Token> _tokens;
        std::vector<Token>::iterator _currentToken;
    };

}
