#include "Parser.hpp"

namespace PiouC
{

    Parser::Parser(Lexer &lex)
        :lex(lex), current_tok(Token::Unknown)
    {}

    Parser::~Parser()
    {}

}
