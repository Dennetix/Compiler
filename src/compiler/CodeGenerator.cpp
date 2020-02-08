#include "CodeGenerator.h"

namespace com {

    std::string CodeGenerator::generate(const Program& program, const std::vector<std::string>& symbols)
    {
        _ss.clear();
        _branchNum = 0;

        _ss << "\t.data" << std::endl;
        for (std::string s : symbols)
            _ss << "w_" << s << ":\t.word 0" << std::endl;
        _ss << "\t.text" << std::endl;
        _ss << "\t.globl main" << std::endl;
        _ss << "main:" << std::endl;

        for (auto i = program.statements.begin(); i != program.statements.end(); i++)
            _genStatement(i->get());

        _ss << "\tjr $ra" << std::endl;

        return _ss.str();
    }

    void CodeGenerator::_genStatement(const Statement* stmt)
    {
        switch (stmt->type)
        {
        case Statement::StatementType::BLOCK:
        {
            auto s = reinterpret_cast<const CompoundStatement*>(stmt);
            for (auto i = s->statements.begin(); i != s->statements.end(); i++)
                _genStatement(i->get());
            break;
        }
        case Statement::StatementType::CONDITIONAL:
        {
            auto s = reinterpret_cast<const ConditionalCompoundStatement*>(stmt);
            int n = ++_branchNum;
            _genExpression(s->condition.get());
            _ss << "\tbeq $a0 $zero con_end_" << n << std::endl;
            _genStatement(s->body.get());
            _ss << "con_end_" << n << ":" << std::endl;
            break;
        }
        case Statement::StatementType::LOOP:
        {
            auto s = reinterpret_cast<const ConditionalCompoundStatement*>(stmt);
            int n = ++_branchNum;
            _ss << "loop_start_" << n << ":" << std::endl;
            _genExpression(s->condition.get());
            _ss << "\tbeq $a0 $zero loop_end_" << n << std::endl;
            _genStatement(s->body.get());
            _ss << "\tb loop_start_" << n << std::endl;
            _ss << "loop_end_" << n << ":" << std::endl;
            break;
        }
        case Statement::StatementType::OUTPUT:
        {
            auto s = reinterpret_cast<const ExpressionStatement*>(stmt);
            _genExpression(s->expression.get());
            _ss << "\tli $v0 1" << std::endl;
            _ss << "\tsyscall" << std::endl;
            _ss << "\tli $v0 11" << std::endl;
            _ss << "\tli $a0 10" << std::endl;
            _ss << "\tsyscall" << std::endl;
            break;
        }
        case Statement::StatementType::EXPRESSION:
        {
            auto s = reinterpret_cast<const ExpressionStatement*>(stmt);
            _genExpression(s->expression.get());
            break;
        }
        }
    }

    void CodeGenerator::_genExpression(const Expression* expr)
    {
        switch (expr->type)
        {
        case Expression::ExpressionType::LITERAL:
        {
            auto e = reinterpret_cast<const LiteralExpression*>(expr);
            if (e->expressionType == TokenType::NUMBER)
                _ss << "\tli $a0 " << e->value << std::endl;
            else
                _ss << "\tlw $a0 w_" << e->value << std::endl;
            break;
        }
        case Expression::ExpressionType::BINARY:
        {
            auto e = reinterpret_cast<const BinaryExpression*>(expr);
            int n = ++_branchNum;
            _genExpression(e->right.get());
            if (e->expressionType == TokenType::OP_ASSIGN)
            {
                auto left = reinterpret_cast<const LiteralExpression*>(e->left.get());
                _ss << "\tsw $a0 w_" << left->value << std::endl;
            }
            else
            {
                _ss << "\taddiu $sp $sp -4" << std::endl;
                _ss << "\tsw $a0 0($sp)" << std::endl;
                _genExpression(e->left.get());
                _ss << "\tlw $t1 0($sp)" << std::endl;
                _ss << "\taddiu $sp $sp 4" << std::endl;
                switch (e->expressionType)
                {
                case TokenType::OP_ADD:
                    _ss << "\taddu $a0 $a0 $t1" << std::endl;
                    break;
                case TokenType::OP_SUB:
                    _ss << "\tsubu $a0 $a0 $t1" << std::endl;
                    break;
                case TokenType::OP_MUL:
                    _ss << "\tmulu $a0 $a0 $t1" << std::endl;
                    break;
                case TokenType::OP_DIV:
                    _ss << "\tdivu $a0 $a0 $t1" << std::endl;
                    break;
                case TokenType::OP_MUD:
                    _ss << "\tdivu $a0 $t1" << std::endl;
                    _ss << "\tmfhi $a0" << std::endl;
                    break;
                case TokenType::OP_EQUALS:
                    _ss << "\tbeq $a0 $t1 equ_true_" << n << std::endl;
                    _ss << "\tli $a0 0" << std::endl;
                    _ss << "\tb equ_end_" << n << std::endl;
                    _ss << "equ_true_" << n << ":" << std::endl;
                    _ss << "\tli $a0 1" << std::endl;
                    _ss << "equ_end_" << n << ":" << std::endl;
                    break;
                case TokenType::OP_LESS_THAN:
                    _ss << "\tslt $a0 $a0 $t1" << std::endl;
                    _ss << "\tbeq $a0 1 lt_true_" << n << std::endl;
                    _ss << "\tli $a0 0" << std::endl;
                    _ss << "\tb lt_end_" << n << std::endl;
                    _ss << "lt_true_" << n << ":" << std::endl;
                    _ss << "\tli $a0 1" << std::endl;
                    _ss << "lt_end_" << n << ":" << std::endl;
                    break;
                case TokenType::OP_GREATER_THAN:
                    _ss << "\tslt $a0 $t1 $a0" << std::endl;
                    _ss << "\tbeq $a0 1 gt_true_" << n << std::endl;
                    _ss << "\tli $a0 0" << std::endl;
                    _ss << "\tb gt_end_" << n << std::endl;
                    _ss << "gt_true_" << n << ":" << std::endl;
                    _ss << "\tli $a0 1" << std::endl;
                    _ss << "gt_end_" << n << ":" << std::endl;
                    break;
                case TokenType::LOP_AND:
                    _ss << "\tbne $a0 1 land_false_" << n << std::endl;
                    _ss << "\tbne $t1 1 land_false_" << n << std::endl;
                    _ss << "\tli $a0 1" << std::endl;
                    _ss << "\tb land_end_" << n << std::endl;
                    _ss << "land_false_" << n << ":" << std::endl;
                    _ss << "\tli $a0 0" << std::endl;
                    _ss << "land_end_" << n << ":" << std::endl;
                    break;
                case TokenType::LOP_OR:
                    _ss << "\tbeq $a0 1 lor_true_" << n << std::endl;
                    _ss << "\tbeq $t1 1 lor_true_" << n << std::endl;
                    _ss << "\tli $a0 0" << std::endl;
                    _ss << "\tb lor_end_" << n << std::endl;
                    _ss << "lor_true_" << n << ":" << std::endl;
                    _ss << "\tli $a0 1" << std::endl;
                    _ss << "lor_end_" << n << ":" << std::endl;
                    break;
                }
            }
            break;
        }
        case Expression::ExpressionType::UNARY:
        {
            auto e = reinterpret_cast<const UnaryExpression*>(expr);
            int n = ++_branchNum;
            _genExpression(e->expression.get());
            if (e->expressionType == TokenType::LOP_NOT)
            {
                _ss << "\tbeq $a0 $zero lnot_true_" << n << std::endl;
                _ss << "\tli $a0 0" << std::endl;
                _ss << "\tb lnot_end_" << n << std::endl;
                _ss << "lnot_true_" << n << ":" << std::endl;
                _ss << "\tli $a0 1" << std::endl;
                _ss << "lnot_end_" << n << ":" << std::endl;
            }
            else
            {
                _ss << "\tsubu $a0, $zero, $a0" << std::endl;
            }
            break;
        }
        }
    }

}
