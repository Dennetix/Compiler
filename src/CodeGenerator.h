#pragma once

#include <sstream>

#include "utils/ASTTypes.h"

namespace com {

    class CodeGenerator
    {
    public:
        std::string generate(const Program& program);

    private:
        void _genStatement(const Statement* stmt);
        void _genExpression(const Expression* expr);

    private:
        std::stringstream _ss;
        int _branchNum;
    };

}
