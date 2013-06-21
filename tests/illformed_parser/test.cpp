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

void run_missing_type()
{
    try
    {
        std::ifstream file("./missing_type.piou");

        if (!file)
            throw TestMessage("Can't open test file");
        Lexer lex(file);
        Parser parser(lex);
        while (parser.get_next_expression());
    }
    catch(ParserException &e)
    {
        if (e.get_type() == ParserExceptionType::ExpectedType)
            return;
        throw e;
    }
    throw TestMessage("Illformed file accepted");
}

void run_expected_end_of_arg()
{
    try
    {
        std::ifstream file("./expected_end_of_arg.piou");

        if (!file)
            throw TestMessage("Can't open test file");
        Lexer lex(file);
        Parser parser(lex);
        while (parser.get_next_expression());
    }
    catch(ParserException &e)
    {
        if (e.get_type() == ParserExceptionType::ExpectedEndOfArg)
            return;
        throw e;
    }
    throw TestMessage("Illformed file accepted");
}

void run_expected_start_arg()
{
    try
    {
        std::ifstream file("./expected_start_arg.piou");

        if (!file)
            throw TestMessage("Can't open test file");
        Lexer lex(file);
        Parser parser(lex);
        while (parser.get_next_expression());
    }
    catch(ParserException &e)
    {
        if (e.get_type() == ParserExceptionType::ExpectedStartArg)
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

    success &= run("Check parser : Expected type (while reading proto args)", run_missing_type);
    success &= run("Check parser : Expected end of arg", run_expected_end_of_arg);
    success &= run("Check parser : Expected start arg", run_expected_start_arg);

    if (success)
        return EXIT_SUCCESS;
    return EXIT_FAILURE;
}
