#ifndef PARSER_HPP_
#define PARSER_HPP_

#include "Lexer.hpp"
#include "AST.hpp"

namespace PiouC
{

    class Parser
    {
    public:
        Parser(Lexer &lex);
        ~Parser();
    private:
        Lexer &lex;

        Token current_tok;

        inline Token
        get_next_token();
    };

}

#include "Parser.imp"

#endif /* !PARSER_HPP_ */
