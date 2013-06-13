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
        Identifier,
        Number,
        Unknown,
    };
};

#endif /* !TOKEN_HPP_ */
