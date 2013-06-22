#include <cstdlib>
#include <iostream>

#include "Lexer.hpp"
#include "LexerException.hpp"
#include "Parser.hpp"
#include "ParserException.hpp"
#include "AST.hpp"
#include "CodeGenerator.hpp"

using namespace PiouC;

void lexer_state(const Lexer &lex) noexcept
{
    std::string consumed_line = lex.get_consumed_line();
    std::cout << "The lexer was reading the line "
              << lex.get_current_line()
              << " at column number "
              << consumed_line.length()
              << ":"
              << std::endl;
    std::cout << "    "
              << consumed_line
              << std::endl;
    std::cout.width(consumed_line.length() + 4);
    std::cout.fill(' ');
    std::cout << "^"
              << std::endl;
    std::cout << "The internal state was "
              << "<string value: "
              << lex.get_last_token_value<std::string>()
              << ", integer value: "
              << lex.get_last_token_value<int>()
              << ", floating value: "
              << lex.get_last_token_value<double>()
              << ">"
              << std::endl;
    std::cout << "The last character read was "
              << "'" << lex.get_last_token_value<char>() << "'"
              << "."
              << std::endl;
}

void parser_state(const Parser &parser)
{
    std::cout << "Parser state : "
              << parser.get_current_token()
              << std::endl;
}

int main(int argc, char *argv[])
{
    Lexer lex(std::cin);
    Parser parser(lex);
    CodeGenerator codegen;

    try
    {
        PExprAST expr;
        while ((expr = parser.get_next_expression()))
        {
            std::cout << "Expression :" << std::endl;
            lexer_state(lex);
            if (expr)
                expr->accept(codegen);
        }
    }
    catch (LexerException &e)
    {
        std::cout << "Lexer failed : " << e.what() << std::endl;
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
