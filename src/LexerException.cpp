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
        switch (type)
        {
        case LexerExceptionType::InvalidCharacter:
            return "Invalid character";
        case LexerExceptionType::UnexpectedSymbolAfterLiteral:
            return "Unexpected symbol after literal";
        case LexerExceptionType::UnexpectedSymbolAfterNumber:
            return "Unexpected symbol after number";
        case LexerExceptionType::UnexpectedEOF:
            return "Unexpected end of file";
        default:
            return "Lexer failed";
        }
    }

    LexerExceptionType
    LexerException::get_type() const noexcept
    {
        return type;
    }
}
