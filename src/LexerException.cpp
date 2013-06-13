#include "LexerException.hpp"

namespace PiouC
{
    LexerException::LexerException(LexerExceptionType type)
        :type(type)
    {}

    LexerException::~LexerException()
    {}

    const char*
    LexerException::what() const noexcept
    {
        return "Lexer failed";
    }

    LexerExceptionType
    LexerException::get_type() const noexcept
    {
        return type;
    }
}
