#include "Parser.hpp"
#include "ParserException.hpp"

namespace PiouC
{

    Parser::Parser(Lexer &lex)
        :lex(lex), current_tok(Token::Unknown)
    {}

    Parser::~Parser()
    {}

    PExprAST
    Parser::parse_integer_expr() noexcept
    {
        PExprAST node = PExprAST(new IntegerExprAST(lex.get_last_token_value<int>()));
        get_next_token(); // eat integer
        return node;
    }

    PExprAST
    Parser::parse_float_expr() noexcept
    {
        PExprAST node = PExprAST(new FloatingExprAST(lex.get_last_token_value<float>()));
        get_next_token(); // eat float
        return node;
    }

    PExprAST
    Parser::parse_string_expr() noexcept
    {
        PExprAST node = PExprAST(new StringExprAST(lex.get_last_token_value<std::string>()));
        get_next_token(); // eat string
        return node;
    }

    PExprAST
    Parser::parse_parenth_expr()
    {
        get_next_token(); // eat '('
        PExprAST node = parse_expr();
        if (current_tok != Token::CloseParenthesis)
            throw ParserException(ParserExceptionType::ExpectedEndOfInstr);
        get_next_token(); // eat ')'
        return node;
    }

    PExprAST
    Parser::parse_identifier_expr()
    {
        std::string identifier = lex.get_last_token_value<std::string>();
        get_next_token(); // eat identifier

        //If it's a simple identifier
        if (current_tok != Token::StartArg)
            return PExprAST(new VariableExprAST(identifier));

        //It's a function call :
        get_next_token(); // eat '<'
        std::vector<PExprAST> args;
        while (current_tok != Token::EndArg)
        {
            PExprAST expr = parse_expr();
            if (current_tok != Token::ArgSep && current_tok != Token::EndArg)
                throw ParserException(ParserExceptionType::ExpectedEndOfArg);
        }
        get_next_token(); // eat ')'

        return PExprAST(new CallExprAST(identifier, args));
    }

    PExprAST
    Parser::parse_expr()
    {
        return nullptr;
    }

}
