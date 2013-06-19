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
        case ParserExceptionType::UnknowType:
            return "Tryed to convert a token to a variable type, but failed";
        case ParserExceptionType::ExpectedIdentifier:
            return "Expected an identifier while reading a prototype or variable declaration";
        case ParserExceptionType::ExpectedStartArg:
            return "Expected an start arg operator ('<')";
        case ParserExceptionType::ExpectedType:
            return "Expected a type (String, Integer, Floating)";
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
