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
    protected:
        //! Parse integer literal
        PExprAST parse_integer_expr() noexcept;
        //! Parse float literal
        PExprAST parse_float_expr() noexcept;
        //! Parse string literal
        PExprAST parse_string_expr() noexcept;

        //! Parse expression
        PExprAST parse_expr();

        //! Parse identifier and function call
        PExprAST parse_identifier_expr();

        PExprAST parse_parenth_expr();
    private:
        Lexer &lex;

        Token current_tok;

        inline Token
        get_next_token();
    };

}

#include "Parser.imp"

#endif /* !PARSER_HPP_ */
