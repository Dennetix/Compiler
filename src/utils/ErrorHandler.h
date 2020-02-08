#pragma once

#include <utility>
#include <string>
#include <vector>

namespace com {

    class ErrorHandler
    {
    public:
        static void addError(const std::string& error, bool abort = false);
        static bool printErrors();

    private:
        static std::vector<std::pair<std::string, bool>> _errors;
    };

}
