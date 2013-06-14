#ifndef PARSER_EXCEPTION_HPP_
# define PARSER_EXCEPTION_HPP_

#include "Exception.hpp"

namespace PiouC
{
    enum class ParserExceptionType
    {
        ExpectedEndOfInstr,
        ExpectedEndOfParenth,
        ExpectedEndOfArg,
    };

    class ParserException : public virtual Exception
    {
    public:
        ParserException(ParserExceptionType type);
        ~ParserException();

        virtual const char *what() const noexcept;

        ParserExceptionType get_type() const noexcept;
    private:
        ParserExceptionType type;
    };
}

#endif /* !PARSER_EXCEPTION_HPP_ */
