#include "Exception.hpp"

namespace PiouC
{
    const char *Exception::what() const noexcept
    {
        return "PiouC Exception";
    }
}
