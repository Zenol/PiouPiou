#ifndef CODE_GENERATOR_EXCEPTION_HPP_
# define CODE_GENERATOR_EXCEPTION_HPP_

#include "Exception.hpp"

namespace PiouC
{
    enum class CGExceptionType
    {
        UnknownBinaryOperator,
        ExpectedVariable,
        TooFewArguments,
        TooMuchArguments,
        Unknown,
    };

    class CGException : public virtual Exception
    {
    public:
        CGException(CGExceptionType type);
        ~CGException();

        virtual const char *what() const noexcept;

        CGExceptionType get_type() const noexcept;
    private:
        CGExceptionType type;
    };
}

#endif /* !CODE_GENERATOR_EXCEPTION_HPP_ */
