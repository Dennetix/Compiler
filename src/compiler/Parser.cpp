#include "Parser.h"

#include "../utils/Exception.h"
#include "../utils/ErrorHandler.h"

namespace com {

    Program Parser::parse(const std::vector<Token>& _tokens)
    {
        this->_tokens = _tokens;
        _currentToken = this->_tokens.begin();

        Program program;

        try
        {
            program.statements = _parseStatements();
            if (_currentToken->first != TokenType::EOI)
                throw Exception("unexpected token " + tokenTypeToString(_currentToken->first));
        }
        catch (const std::exception& e)
        {
            ErrorHandler::addError("Parsing error: " + std::string(e.what()), true);
        }

        return program;
    }

    void Parser::_nextToken()
    {
        if (_currentToken != _tokens.end())
            _currentToken++;
    }

    bool Parser::_acceptToken(TokenType type)
    {
        if (_currentToken->first != type)
            return false;
        _nextToken();
        return true;
    }

    void Parser::_expectToken(TokenType type)
    {
        if (!_acceptToken(type))
            throw Exception("unexpected token " + tokenTypeToString(_currentToken->first) + ", expected token " + tokenTypeToString(type));
    }

    std::vector<std::unique_ptr<Statement>> Parser::_parseStatements()
    {
        std::vector<std::unique_ptr<Statement>> stmts;
        std::unique_ptr<Statement> s;
        while (s = _parseStatement())
            stmts.push_back(std::move(s));
        return stmts;
    }

    std::unique_ptr<Statement> Parser::_parseStatement()
    {
        if (_acceptToken(TokenType::OPEN_CURLY_BRACKET))
        {
            std::unique_ptr<CompoundStatement> s(new CompoundStatement(Statement::StatementType::BLOCK));
            s->statements = _parseStatements();
            _expectToken(TokenType::CLOSE_CURLY_BRACKET);
            return s;
        }
        else if (_acceptToken(TokenType::KEY_IF))
        {
            std::unique_ptr<ConditionalCompoundStatement> s(new ConditionalCompoundStatement(Statement::StatementType::CONDITIONAL));
            _expectToken(TokenType::OPEN_BRACKET);
            if (!(s->condition = _parseExpression()))
                throw Exception("expected expression as condition in conditional statement");
            _expectToken(TokenType::CLOSE_BRACKET);
            if (!(s->body = _parseStatement()))
                throw Exception("expected statement as body in conditional statement");
            return s;
        }
        else if (_acceptToken(TokenType::KEY_WHILE))
        {
            std::unique_ptr<ConditionalCompoundStatement> s(new ConditionalCompoundStatement(Statement::StatementType::LOOP));
            _expectToken(TokenType::OPEN_BRACKET);
            if (!(s->condition = _parseExpression()))
                throw Exception("expected expression as condition in loop statement");
            _expectToken(TokenType::CLOSE_BRACKET);
            if (!(s->body = _parseStatement()))
                throw Exception("expected statement as body in loop statement");
            return s;
        }
        else if (_acceptToken(TokenType::KEY_OUT))
        {
            std::unique_ptr<ExpressionStatement> s(new ExpressionStatement(Statement::StatementType::OUTPUT));
            _expectToken(TokenType::OPEN_BRACKET);
            if (!(s->expression = _parseExpression()))
                throw Exception("expected expression in output statement");
            _expectToken(TokenType::CLOSE_BRACKET);
            _expectToken(TokenType::SEMICOLON);
            return s;
        }
        else if (_acceptToken(TokenType::SEMICOLON))
        {
            return std::unique_ptr<Statement>(new Statement(Statement::StatementType::NOOP));
        }

        std::unique_ptr<ExpressionStatement> s(new ExpressionStatement(Statement::StatementType::EXPRESSION));
        if (s->expression = _parseExpression())
        {
            _expectToken(TokenType::SEMICOLON);
            return s;
        }
        return nullptr;
    }

    std::unique_ptr<Expression> Parser::_parseExpression()
    {
        std::unique_ptr<Expression> left = _parseLogicalOr();
        if (left)
        {
            while (_acceptToken(TokenType::OP_ASSIGN))
            {
                std::unique_ptr<BinaryExpression> e(new BinaryExpression(Expression::ExpressionType::BINARY, TokenType::OP_ASSIGN));
                e->left = std::move(left);
                if (!(e->right = _parseLogicalOr()))
                    throw Exception("expected expression after token " + tokenTypeToString(TokenType::OP_ASSIGN));
                left = std::move(e);
            }
            return left;
        }
        return nullptr;
    }

    std::unique_ptr<Expression> Parser::_parseLogicalOr()
    {
        std::unique_ptr<Expression> left = _parseLogicalAnd();
        if (left)
        {
            while (_acceptToken(TokenType::LOP_OR))
            {
                std::unique_ptr<BinaryExpression> e(new BinaryExpression(Expression::ExpressionType::BINARY, TokenType::LOP_OR));
                e->left = std::move(left);
                if (!(e->right = _parseLogicalAnd()))
                    throw Exception("expected expression after token " + tokenTypeToString(TokenType::LOP_OR));
                left = std::move(e);
            }
            return left;
        }
        return nullptr;
    }

    std::unique_ptr<Expression> Parser::_parseLogicalAnd()
    {
        std::unique_ptr<Expression> left = _parseEquals();
        if (left)
        {
            while (_acceptToken(TokenType::LOP_AND))
            {
                std::unique_ptr<BinaryExpression> e(new BinaryExpression(Expression::ExpressionType::BINARY, TokenType::LOP_AND));
                e->left = std::move(left);
                if (!(e->right = _parseEquals()))
                    throw Exception("expected expression after token " + tokenTypeToString(TokenType::LOP_AND));
                left = std::move(e);
            }
            return left;
        }
        return nullptr;
    }

    std::unique_ptr<Expression> Parser::_parseEquals()
    {
        std::unique_ptr<Expression> left = _parseLessGreaterThan();
        if (left)
        {
            while (_acceptToken(TokenType::OP_EQUALS))
            {
                std::unique_ptr<BinaryExpression> e(new BinaryExpression(Expression::ExpressionType::BINARY, TokenType::OP_EQUALS));
                e->left = std::move(left);
                if (!(e->right = _parseLessGreaterThan()))
                    throw Exception("expected expression after token " + tokenTypeToString(TokenType::OP_EQUALS));
                left = std::move(e);
            }
            return left;
        }
        return nullptr;
    }

    std::unique_ptr<Expression> Parser::_parseLessGreaterThan()
    {
        std::unique_ptr<Expression> left = _parseSum();
        if (left)
        {
            while (_currentToken->first == TokenType::OP_LESS_THAN || _currentToken->first == TokenType::OP_GREATER_THAN)
            {
                TokenType type = _currentToken->first;
                std::unique_ptr<BinaryExpression> e(new BinaryExpression(Expression::ExpressionType::BINARY, type));
                _nextToken();
                e->left = std::move(left);
                if (!(e->right = _parseSum()))
                    throw Exception("expected expression after token " + tokenTypeToString(type));
                left = std::move(e);
            }
            return left;
        }
        return nullptr;
    }

    std::unique_ptr<Expression> Parser::_parseSum()
    {
        std::unique_ptr<Expression> left = _parseProduct();
        if (left)
        {
            while (_currentToken->first == TokenType::OP_ADD || _currentToken->first == TokenType::OP_SUB)
            {
                TokenType type = _currentToken->first;
                std::unique_ptr<BinaryExpression> e(new BinaryExpression(Expression::ExpressionType::BINARY, type));
                _nextToken();
                e->left = std::move(left);
                if (!(e->right = _parseProduct()))
                    throw Exception("expected expression after token " + tokenTypeToString(type));
                left = std::move(e);
            }
            return left;
        }
        return nullptr;
    }

    std::unique_ptr<Expression> Parser::_parseProduct()
    {
        std::unique_ptr<Expression> left = _parseLogicalNot();
        if (left)
        {
            while (_currentToken->first == TokenType::OP_MUL || _currentToken->first == TokenType::OP_DIV || _currentToken->first == TokenType::OP_MUD)
            {
                TokenType type = _currentToken->first;
                std::unique_ptr<BinaryExpression> e(new BinaryExpression(Expression::ExpressionType::BINARY, type));
                _nextToken();
                e->left = std::move(left);
                if (!(e->right = _parseLogicalNot()))
                    throw Exception("expected expression after token " + tokenTypeToString(type));
                left = std::move(e);
            }
            return left;
        }
        return nullptr;
    }

    std::unique_ptr<Expression> Parser::_parseLogicalNot()
    {
        if (_acceptToken(TokenType::LOP_NOT))
        {
            std::unique_ptr<UnaryExpression> e(new UnaryExpression(Expression::ExpressionType::UNARY, TokenType::LOP_NOT));
            if (!(e->expression = _parseUnaryMinus()))
                throw Exception("expected expression after token " + tokenTypeToString(TokenType::LOP_NOT));
            return e;
        }
        return _parseUnaryMinus();
    }

    std::unique_ptr<Expression> Parser::_parseUnaryMinus()
    {
        if (_acceptToken(TokenType::OP_SUB))
        {
            std::unique_ptr<UnaryExpression> e(new UnaryExpression(Expression::ExpressionType::UNARY, TokenType::OP_SUB));
            if (!(e->expression = _parseExpression()))
                throw Exception("expected expression after token " + tokenTypeToString(TokenType::OP_SUB));
            return e;
        }
        return _parseLiteral();
    }

    std::unique_ptr<Expression> Parser::_parseLiteral()
    {
        if (_acceptToken(TokenType::OPEN_BRACKET))
        {
            auto e = _parseExpression();
            if (!e)
                throw Exception("expected expression after token " + tokenTypeToString(TokenType::OPEN_BRACKET));
            _expectToken(TokenType::CLOSE_BRACKET);
            return e;
        }
        else if (_currentToken->first == TokenType::SYMBOL || _currentToken->first == TokenType::NUMBER)
        {
            std::unique_ptr<LiteralExpression> e(new LiteralExpression(Expression::ExpressionType::LITERAL, _currentToken->first));
            e->value = _currentToken->second;
            _nextToken();
            return e;
        }
        return nullptr;
    }


}
