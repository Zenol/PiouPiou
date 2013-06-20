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

        Token
        get_token();

        template<class T>
        inline T
        get_last_token_value() const noexcept;

        inline int
        get_current_line() const noexcept;

        inline std::string
        get_consumed_line() const noexcept;
    private:
        int line_number;
        std::string consumed_line;
        std::string input;

        int         c;
        std::string last_token_string;
        int         last_token_int;
        float       last_token_float;

        std::istream &iss;

        Token
        check(Token type);

        Token
        read_string();

        Token
        read_comment();

        Token
        read_number();

        Token
        convert_number(Token type);

        inline int
        get_char();
    };

}
#include "Lexer.imp"

#endif /* !LEXER_HPP_ */
