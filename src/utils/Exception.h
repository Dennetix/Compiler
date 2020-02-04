#pragma once

#include <exception>
#include <string>

namespace com {

    class Exception
        : public std::exception
    {
    public:
        Exception(const std::string& msg);
        virtual const char* what() const noexcept;

    private:
        std::string _msg;
    };

}
