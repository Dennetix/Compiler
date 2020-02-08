#include "ErrorHandler.h"

#include <iostream>

namespace com {

    std::vector<std::pair<std::string, bool>> ErrorHandler::_errors;

    void ErrorHandler::addError(const std::string& error, bool abort)
    {
        _errors.push_back({ error, abort });
    }

    bool ErrorHandler::printErrors()
    {
        bool abort = false;
        for (auto e : _errors)
        {
            std::cerr << e.first << std::endl;
            if (e.second)
                abort = true;
        }
        if (abort)
        {
            std::cerr << "Compilation aborted with " << _errors.size();
            if (_errors.size() == 1)
                std::cerr << " error" << std::endl;
            else
                std::cerr << " errors" << std::endl;
            return true;
        }
        _errors.clear();
        return false;
    }

}
