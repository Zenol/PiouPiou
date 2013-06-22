#ifndef LEXER_EXCEPTION_HPP_
#define LEXER_EXCEPTION_HPP_

#include "Exception.hpp"

namespace PiouC
{
    enum class LexerExceptionType
    {
        InvalidCharacter,
        UnexpectedSymbolAfterLiteral,
        UnexpectedSymbolAfterNumber,
        UnexpectedEOF,
        Unknown,
    };

    class LexerException : public virtual Exception
    {
    public:
        LexerException(LexerExceptionType type);
        ~LexerException();

        virtual const char *what() const noexcept;

        LexerExceptionType get_type() const noexcept;
    private:
        LexerExceptionType type;
    };
}

#endif /* !LEXER_EXCEPTION_HPP_ */
