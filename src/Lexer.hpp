#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <istream>

#include "Token.hpp"

namespace PiouC
{
    class Lexer
    {
    public:
        Lexer(std::istream &iss);
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
        float       last_token_float;

        std::istream &iss;

        Token
        check(int c, Token type);
        Token
        read_string();
        Token
        read_comment();
        Token
        read_number(int c);
        Token
        convert_number(Token type);
    };

}
#include "Lexer.imp"

#endif /* !LEXER_HPP_ */
