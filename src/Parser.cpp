#include "Parser.hpp"

namespace PiouC
{

    Parser::Parser(Lexer &lex)
        :lex(lex), current_tok(Token::Unknown)
    {}

    Parser::~Parser()
    {}

    PExprAST
    Parser::ParseIntegerExpr() noexcept
    {
        return PExprAST(new IntegerExprAST(lex.get_last_token_value<int>()));
    }

    PExprAST
    Parser::ParseFloatExpr() noexcept
    {
        return PExprAST(new FloatingExprAST(lex.get_last_token_value<float>()));
    }

    PExprAST
    Parser::ParseStringExpr() noexcept
    {
        return PExprAST(new StringExprAST(lex.get_last_token_value<std::string>()));
    }

}
