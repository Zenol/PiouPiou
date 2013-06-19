#include <cstdlib>
#include <iostream>

#include "Lexer.hpp"
#include "LexerException.hpp"
#include "Parser.hpp"
#include "ParserException.hpp"
#include "AST.hpp"

using namespace PiouC;

void lexer_state(const Lexer &lex)
{
    std::cout << "Lexer state : "
              << "c:" << lex.get_last_token_value<char>()
              << " | s:"
              << lex.get_last_token_value<std::string>()
              << " | i:"
              << lex.get_last_token_value<int>()
              << " | f:"
              << lex.get_last_token_value<float>()
              << std::endl;
}

void parser_state(const Parser &parser)
{
    std::cout << "Parser state :"
              << parser.get_current_token()
              << std::endl;
}

int main(int argc, char *argv[])
{
    Lexer lex(std::cin);
    Parser parser(lex);

    try
    {
        PExprAST expr;
        while ((expr = parser.get_next_expression()))
        {
            std::cout << "Expression :" << std::endl;
            lexer_state(lex);
        }
    }
    catch (LexerException &e)
    {
        std::cout << "LexerException" << e.what() << std::endl;
        lexer_state(lex);
        return EXIT_FAILURE;
    }
    catch (ParserException &e)
    {
        std::cout << "Parser failed : " << e.what() << std::endl;
        lexer_state(lex);
        parser_state(parser);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
