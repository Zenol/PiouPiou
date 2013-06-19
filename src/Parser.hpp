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
        //! Parse floating number literal
        PExprAST parse_floating_expr() noexcept;
        //! Parse string literal
        PExprAST parse_string_expr() noexcept;

        //! Parse expression
        PExprAST parse_expr();

        //! Parse identifier and function call
        PExprAST parse_identifier_expr();

        //! Parse an expression enclosed by parentheses.
        PExprAST parse_parenth_expr();

        //! Parse a primary expression (identifier, literals, parentheses)
        PExprAST parse_primary();
    private:
        Lexer &lex;

        Token current_tok;

        inline Token
        get_next_token();
    };

}

#include "Parser.imp"

#endif /* !PARSER_HPP_ */
