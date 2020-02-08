#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Token.h"

namespace com {

    struct Statement;

    struct Expression
    {
        enum class ExpressionType
        {
            LITERAL,
            BINARY,
            UNARY
        };

        Expression(ExpressionType type);

        ExpressionType type;
    };

    struct LiteralExpression
        : Expression
    {
        LiteralExpression(ExpressionType type, TokenType expressionType);

        TokenType expressionType;
        std::string value;
    };

    struct BinaryExpression
        : Expression
    {
        BinaryExpression(ExpressionType type, TokenType expressionType);

        TokenType expressionType;
        std::unique_ptr<Expression> left;
        std::unique_ptr<Expression> right;
    };

    struct UnaryExpression
        : Expression
    {
        UnaryExpression(ExpressionType type, TokenType expressionType);

        TokenType expressionType;
        std::unique_ptr<Expression> expression;
    };

    struct Statement
    {
        enum class StatementType
        {
            BLOCK,
            CONDITIONAL,
            LOOP,
            OUTPUT,
            EXPRESSION,
            NOOP
        };

        Statement(StatementType type);

        StatementType type;
    };

    struct CompoundStatement
        : Statement
    {
        using Statement::Statement;

        std::vector<std::unique_ptr<Statement>> statements;
    };

    struct ConditionalCompoundStatement
        : Statement
    {
        using Statement::Statement;

        std::unique_ptr<Expression> condition;
        std::unique_ptr<Statement> body;
    };

    struct ExpressionStatement
        : Statement
    {
        using Statement::Statement;

        std::unique_ptr<Expression> expression;
    };

    class Program
    {
    public:
        void print();

    public:
        std::vector<std::unique_ptr<Statement>> statements;

    private:
        void _printStatement(const Statement* stmt);
        void _printExpression(const Expression* expr);

        void _printIndented(const std::string& str) const;

    private:
        int _indent;
    };

}
