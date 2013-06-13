#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <istream>

#include "Token.hpp"

namespace PiouC
{
    class Lexer
    {
    public:
        Lexer(std::istream iss);
        ~Lexer();

        Token get_token();

        template<class T>
        inline
        T get_last_token_value() const;
    private:
        std::string input;

        std::string last_token_string;
        int         last_token_int;
        char        last_token_char;
    };

}
#include "Lexer.imp"

#endif /* !LEXER_HPP_ */
