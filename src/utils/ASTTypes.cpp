#include "ASTTypes.h"

#include <iostream>

namespace com {

    Expression::Expression(ExpressionType type)
        : type(type)
    { }

    LiteralExpression::LiteralExpression(ExpressionType type, TokenType expressionType)
        : Expression(type), expressionType(expressionType)
    { }

    BinaryExpression::BinaryExpression(ExpressionType type, TokenType expressionType)
        : Expression(type), expressionType(expressionType)
    { }

    UnaryExpression::UnaryExpression(ExpressionType type, TokenType expressionType)
        : Expression(type), expressionType(expressionType)
    { }

    Statement::Statement(StatementType t)
        : type(t)
    { }

    void Program::print()
    {
        _indent = -1;
        for (auto s = statements.begin(); s != statements.end(); s++)
            _printStatement(s->get());
    }

    void Program::_printStatement(const Statement* stmt)
    {
        _indent++;
        switch (stmt->type)
        {
        case Statement::StatementType::BLOCK:
        {
            auto s = reinterpret_cast<const CompoundStatement*>(stmt);
            _printIndented("-Statement: Block");
            _printIndented(" Statements:");
            for (auto i = s->statements.begin(); i != s->statements.end(); i++)
                _printStatement(i->get());
            break;
        }
        case Statement::StatementType::CONDITIONAL:
        {
            auto s = reinterpret_cast<const ConditionalCompoundStatement*>(stmt);
            _printIndented("-Statement: Contitional");
            _printIndented(" Condition:");
            _printExpression(s->condition.get());
            _printIndented(" Body:");
            _printStatement(s->body.get());
            break;
        }
        case Statement::StatementType::LOOP:
        {
            auto s = reinterpret_cast<const ConditionalCompoundStatement*>(stmt);
            _printIndented("-Statement: Loop");
            _printIndented(" Condition:");
            _printExpression(s->condition.get());
            _printIndented(" Body:");
            _printStatement(s->body.get());
            break;
        }
        case Statement::StatementType::OUTPUT:
        {
            auto s = reinterpret_cast<const ExpressionStatement*>(stmt);
            _printIndented("-Statement: Output");
            _printIndented(" Expression:");
            _printExpression(s->expression.get());
            break;
        }
        case Statement::StatementType::EXPRESSION:
        {
            auto s = reinterpret_cast<const ExpressionStatement*>(stmt);
            _printIndented("-Statement: Expression");
            _printIndented(" Expression:");
            _printExpression(s->expression.get());
            break;
        }
        case Statement::StatementType::NOOP:
            _printIndented("-Statement: Noop");
            break;
        }
        _indent--;
    }

    void Program::_printExpression(const Expression* expr)
    {
        _indent++;
        switch (expr->type)
        {
        case Expression::ExpressionType::LITERAL:
        {
            auto e = reinterpret_cast<const LiteralExpression*>(expr);
            _printIndented("-Expression: Literal");
            _printIndented(" Type: " + tokenTypeToString(e->expressionType));
            _printIndented(" Value: " + e->value);
            break;
        }
        case Expression::ExpressionType::BINARY:
        {
            auto e = reinterpret_cast<const BinaryExpression*>(expr);
            _printIndented("-Expression: Binary");
            _printIndented(" Type: " + tokenTypeToString(e->expressionType));
            _printIndented(" Left:");
            _printExpression(e->left.get());
            _printIndented(" Right:");
            _printExpression(e->right.get());
            break;
        }
        case Expression::ExpressionType::UNARY:
        {
            auto e = reinterpret_cast<const UnaryExpression*>(expr);
            _printIndented("-Expression: Unary");
            _printIndented(" Type: " + tokenTypeToString(e->expressionType));
            _printIndented(" Expression:");
            _printExpression(e->expression.get());
            break;
        }
        }
        _indent--;
    }

    void Program::_printIndented(const std::string& str) const
    {
        for (int i = 0; i < _indent; i++)
            std::cout << "    ";
        std::cout << str << std::endl;
    }

}
