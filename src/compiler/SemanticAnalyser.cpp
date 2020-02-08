#include "SemanticAnalyser.h"

#include <algorithm>

#include "../utils/ErrorHandler.h"

namespace com {

    std::vector<std::string> SemanticAnalyser::analyse(const Program& program)
    {
        _symbols.clear();

        for (auto i = program.statements.begin(); i != program.statements.end(); i++)
            _analyseStatement(i->get());

        return _symbols;
    }

    void SemanticAnalyser::_analyseStatement(const Statement* stmt)
    {
        switch (stmt->type)
        {
        case Statement::StatementType::BLOCK:
        {
            auto s = reinterpret_cast<const CompoundStatement*>(stmt);
            for (auto i = s->statements.begin(); i != s->statements.end(); i++)
                _analyseStatement(i->get());
            break;
        }
        case Statement::StatementType::CONDITIONAL:
        case Statement::StatementType::LOOP:
        {
            auto s = reinterpret_cast<const ConditionalCompoundStatement*>(stmt);
            _analyseExpression(s->condition.get());
            _analyseStatement(s->body.get());
            break;
        }
        case Statement::StatementType::OUTPUT:
        case Statement::StatementType::EXPRESSION:
        {
            auto s = reinterpret_cast<const ExpressionStatement*>(stmt);
            _analyseExpression(s->expression.get());
            break;
        }
        }
    }

    void SemanticAnalyser::_analyseExpression(const Expression* expr)
    {
        switch (expr->type)
        {
        case Expression::ExpressionType::LITERAL:
        {
            auto e = reinterpret_cast<const LiteralExpression*>(expr);
            if (e->expressionType == TokenType::SYMBOL)
            {
                if (std::find(_symbols.begin(), _symbols.end(), e->value) == _symbols.end())
                    _symbols.push_back(e->value);
            }
            break;
        }
        case Expression::ExpressionType::BINARY:
        {
            auto e = reinterpret_cast<const BinaryExpression*>(expr);
            _analyseExpression(e->right.get());
            if (e->expressionType == TokenType::OP_ASSIGN)
            {
                if (e->left->type == Expression::ExpressionType::LITERAL)
                {
                    auto left = reinterpret_cast<const LiteralExpression*>(e->left.get());
                    if (left->expressionType == TokenType::SYMBOL)
                    {
                        _analyseExpression(e->left.get());
                        return;
                    }
                }
                ErrorHandler::addError("Semantic error: expected symbol as left operand of assignment", true);
            }
            else
            {
                _analyseExpression(e->left.get());
            }
            break;
        }
        case Expression::ExpressionType::UNARY:
        {
            auto e = reinterpret_cast<const UnaryExpression*>(expr);
            _analyseExpression(e->expression.get());
            break;
        }
        }
    }

}
