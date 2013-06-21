#include "Lexer.hpp"
#include "Parser.hpp"
#include "LexerException.hpp"
#include "ParserException.hpp"

#include <cstdlib>
#include <iostream>
#include <fstream>
    #include <unistd.h>
    #define GetCurrentDir getcwd
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

void run_invalid_character()
{
    try
    {
        std::ifstream file("./invalid_character.piou");

        if (!file)
            throw TestMessage("Can't open test file");
        Lexer lex(std::cin);
        Parser parser(lex);
    }
    catch(LexerException &e)
    {
        if (e.get_type() == LexerExceptionType::InvalidCharacter)
            return;
        throw e;
    }
}

void run_missing_type()
{
    try
    {
        std::ifstream file("./missing_type.piou");

        if (!file)
            throw TestMessage("Can't open test file");
        Lexer lex(std::cin);
        Parser parser(lex);
    }
    catch(ParserException &e)
    {
        if (e.get_type() == ParserExceptionType::ExpectedType)
            return;
        throw e;
    }
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
char cCurrentPath[FILENAME_MAX];

 if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
     {
     return errno;
     }

cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

printf ("The current working directory is %s", cCurrentPath);
    bool success = true;
    std::cout <<av[0] << std::endl;
    success &= run("Check lexer  : Invalid Character", run_invalid_character);
    success &= run("Check parser : Missing Type", run_missing_type);

    if (success)
        return EXIT_SUCCESS;
    return EXIT_FAILURE;
}
