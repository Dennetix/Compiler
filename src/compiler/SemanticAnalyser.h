#pragma once

#include "../utils/ASTTypes.h"

namespace com {

    class SemanticAnalyser
    {
    public:
        std::vector<std::string> analyse(const Program& program);

    private:
        void _analyseStatement(const Statement* stmt);
        void _analyseExpression(const Expression* expr);

    private:
        std::vector<std::string> _symbols;
    };

}
