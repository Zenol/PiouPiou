#include "CodeGeneratorException.hpp"

namespace PiouC
{
    CGException::CGException(CGExceptionType type)
        :type(type)
    {}

    CGException::~CGException()
    {}

    const char*
    CGException::what() const noexcept
    {
        switch (type)
        {
        case CGExceptionType::UnknownBinaryOperator:
            return "Can't find implementation of a binary operator";
        case CGExceptionType::ExpectedVariable:
            return "Expected a variable name on left operand of operator ~";
        default:
            return "CG failed";
        }
    }

    CGExceptionType
    CGException::get_type() const noexcept
    {
        return type;
    }
}
