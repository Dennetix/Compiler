#include "SymbolTable.h"

namespace com {

    void SymbolTable::addSymbol(const std::string& symbol, bool declared)
    {
        if (_table.find(symbol) == _table.end())
            _table.insert({ symbol, declared });
    }

    bool SymbolTable::isDeclared(const std::string& symbol)
    {
        auto it = _table.find(symbol);
        if (it != _table.end())
            return it->second;
        _table.insert({ symbol, false });
        return false;
    }

}
