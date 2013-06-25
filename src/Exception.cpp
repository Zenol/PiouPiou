#include "Exception.hpp"

namespace PiouC
{
    const char *Exception::what() const noexcept
    {
        return "PiouC Exception";
    }

    UnsupportedFeature::UnsupportedFeature(const char* string)
        :string(string)
    {}

    const char *UnsupportedFeature::what() const noexcept
    {
        return string;
    }
}
