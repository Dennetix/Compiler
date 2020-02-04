#include "Exception.h"

namespace com {

    Exception::Exception(const std::string& msg)
        : _msg(msg)
    { }

    const char* Exception::what() const noexcept
    {
        return _msg.c_str();
    }

}
