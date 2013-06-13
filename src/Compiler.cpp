#include <cstdlib>
#include <iostream>

#include "Lexer.hpp"
#include "LexerException.hpp"

using namespace PiouC;

int main(int argc, char *argv[])
{
    Lexer lex(std::cin);

    try
    {
        Token tok;
        while ((tok = lex.get_token()) != Token::EndOfFile)
        {
            std::cout << tok
                      << "\t <c:" << lex.get_last_token_value<char>()
                      << " | s:"
                      << lex.get_last_token_value<std::string>()
                      << " | i:"
                      << lex.get_last_token_value<int>()
                      << " | f:"
                      << lex.get_last_token_value<float>()
                      << ">" << std::endl;
        }
    }
    catch (LexerException &e)
    {
        std::cout << "Lexer failed : " << e.what()
                  << "\nNear : "
                  << "c:" << lex.get_last_token_value<char>()
                  << " | s:"
                  << lex.get_last_token_value<std::string>()
                  << " | i:"
                  << lex.get_last_token_value<int>()
                  << " | f:"
                  << lex.get_last_token_value<float>()
                  << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
