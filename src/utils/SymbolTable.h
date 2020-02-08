#pragma once

#include <map>
#include <string>

namespace com {

    class SymbolTable
    {
    public:
        void addSymbol(const std::string& symbol, bool declared = false);
        void setDeclared(const std::string& symbol);
        bool isDeclared(const std::string& symbol);

    private:
        std::map<std::string, bool> _table;
    };

}
