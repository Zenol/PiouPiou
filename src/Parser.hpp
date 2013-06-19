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

        //! Parse the right hand side of binary expression
        //! (For example, parse '+ b' in 'a + b')
        //!
        //! \param precedence_min Minimal precedence that should have the
        //!        operator in the rhs to be accepted. (0 means all
        //!        binary operators).
        //! \param lhs The left hand side expression. In the example above,
        //!            it's 'a'.
        PExprAST parse_binop_rhs(int precedence_min, PExprAST lhs);
    private:
        Lexer &lex;

        Token current_tok;

        inline Token
        get_next_token();

        int
        get_token_precedence();
    };

}

#include "Parser.imp"

#endif /* !PARSER_HPP_ */
