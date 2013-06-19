#ifndef TOKEN_HPP_
#define TOKEN_HPP_

#include <ostream>

namespace PiouC
{
    enum class Token
    {
        Define,
        StartArg,
        EndArg,
        Extern,
        StartContent,
        EndContent,
        EndInstr,
        Identifier,
        Floating,
        Integer,
        String,
        EntryPoint,
        Comment,
        Unknown,
        If,
        Then,
        Else,
        Plus,
        Minus,
        Mult,
        Div,
        Lt,
        Gt,
        Affect,
        StringType,
        FloatingType,
        IntegerType,
        Equal,
        Negate,
        OpenParenthesis,
        CloseParenthesis,
        ArgSep,
        EndOfFile,
    };

    std::ostream& operator<< (std::ostream &out, Token token);
};

#endif /* !TOKEN_HPP_ */
