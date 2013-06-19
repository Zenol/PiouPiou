#include "ParserException.hpp"

namespace PiouC
{
    ParserException::ParserException(ParserExceptionType type)
        :type(type)
    {}

    ParserException::~ParserException()
    {}

    const char*
    ParserException::what() const noexcept
    {
        switch (type)
        {
        case ParserExceptionType::ExpectedEndOfInstr:
            return "Expected end of instruction (':')";
        case ParserExceptionType::ExpectedEndOfParenth:
            return "Expected end of parenthesis (')')";
        case ParserExceptionType::ExpectedEndOfArg:
            return "Expected and of argument list or separator (',' or '>')";
        case ParserExceptionType::ExpectedPrimaryExpr:
            return "Expected a primary expression, but found an unexpected token";
        case ParserExceptionType::BinOpWithoutPrecedence:
            return "A binary operator has no specified precedence";
        default:
            return "Parser failed";
        }
    }

    ParserExceptionType
    ParserException::get_type() const noexcept
    {
        return type;
    }
}
