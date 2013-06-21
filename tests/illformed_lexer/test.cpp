#include "Lexer.hpp"
#include "Parser.hpp"
#include "LexerException.hpp"
#include "ParserException.hpp"

#include <cstdlib>
#include <iostream>
#include <fstream>

class TestMessage : public virtual std::exception
{
public:
    TestMessage(const char* str)
        :msg(str)
    {}

    virtual const char* what() const noexcept
    {
        return msg;
    }

private:
    const char* msg;
};

using namespace PiouC;

void run_unexpected_symbol_literal()
{
    try
    {
        std::ifstream file("./unexpected_symbol_after_literal.piou");

        if (!file)
            throw TestMessage("Can't open test file");
        Lexer lex(file);
        Parser parser(lex);
        while (parser.get_next_expression())
        {};
    }
    catch(LexerException &e)
    {
        if (e.get_type() == LexerExceptionType::UnexpectedSymbolAfterLiteral)
            return;
        throw e;
    }
    throw TestMessage("Illformed file accepted");
}

void run_unexpected_symbol_number()
{
    try
    {
        std::ifstream file("./unexpected_symbol_after_number.piou");

        if (!file)
            throw TestMessage("Can't open test file");
        Lexer lex(file);
        Parser parser(lex);
        while (parser.get_next_expression());
    }
    catch(LexerException &e)
    {
        if (e.get_type() == LexerExceptionType::UnexpectedSymbolAfterNumber)
            return;
        throw e;
    }
    throw TestMessage("Illformed file accepted");
}

void run_unexpected_eof()
{
    try
    {
        std::ifstream file("./unexpected_eof.piou");

        if (!file)
            throw TestMessage("Can't open test file");
        Lexer lex(file);
        Parser parser(lex);
        while (parser.get_next_expression());
    }
    catch(LexerException &e)
    {
        if (e.get_type() == LexerExceptionType::UnexpectedEOF)
            return;
        throw e;
    }
    throw TestMessage("Illformed file accepted");
}

void run_invalid_character()
{
    try
    {
        std::ifstream file("./invalid_character.piou");

        if (!file)
            throw TestMessage("Can't open test file");
        Lexer lex(file);
        Parser parser(lex);
        PExprAST expr;
        while (parser.get_next_expression());
    }
    catch(LexerException &e)
    {
        if (e.get_type() == LexerExceptionType::InvalidCharacter)
            return;
        throw e;
    }
    throw TestMessage("Illformed file accepted");
}

bool run(const char* name, void (*fct) ())
{
    std::string message;
    try
    {
        //If it throw, then it failed
        fct();
        std::cout << "\033[1;7;32m\t" << "[OK] " << name << std::endl;
        return true;
    }
    catch(LexerException &e)
    {
        message = "LexerException : ";
        message += e.what();
    }
    catch(ParserException &e)
    {
        message = "ParserException : ";
        message += e.what();
    }
    catch(TestMessage &e)
    {
        message = "Can't run test : ";
        message += e.what();
    }
    catch(std::exception &e)
    {
        message = "std::exception : ";
        message += e.what();
    }
    catch (...)
    {
        message = "Unknow exception";
    }
    std::cout << "\033[1;7;31m\t" << "[KO] " << name << std::endl;
    std::cout << "\033[0m[Failed] " << message << std::endl;
    return false;
}

int main(int ac, char *av[])
{
    bool success = true;

    success &= run("Check lexer  : Invalid Character", run_invalid_character);
    success &= run("Check lexer  : Unexpected end of file", run_unexpected_eof);
    success &= run("Check lexer  : Unexpected symbol after literal", run_unexpected_symbol_literal);
    success &= run("Check lexer  : Unexpected symbol after number", run_unexpected_symbol_literal);

    if (success)
        return EXIT_SUCCESS;
    return EXIT_FAILURE;
}
