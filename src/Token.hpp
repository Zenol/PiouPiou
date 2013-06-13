#ifndef TOKEN_HPP_
#define TOKEN_HPP_

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
        EndOfFile,
    };
};

#endif /* !TOKEN_HPP_ */
