#include "Lexer.hpp"
#include "LexerException.hpp"

#include <cstdlib>
#include <cassert>

namespace PiouC
{
    static
    inline
    bool
    is_num(int c)
    {
        return (c >= '0' && c <= '9');
    }

    static
    inline
    bool
    is_blank(int c)
    {
        return (c == ' ' || c == '\t' || c == '\r' || c == '\n');
    }


    Lexer::Lexer(std::istream &iss)
        :input(""), c(0),
         last_token_string(""),
         last_token_int(0),
         last_token_float(0.0f),
         iss(iss)
    {}

    Lexer::~Lexer()
    {}

    Token
    Lexer::check(Token type)
    {
        if (!last_token_string.empty())
            throw LexerException(LexerExceptionType::UnexpectedSymbolAfterLiteral);
        return type;
    }

    Token
    Lexer::read_string()
    {
        if (!last_token_string.empty())
            throw LexerException(LexerExceptionType::UnexpectedSymbolAfterLiteral);
        c = iss.get();
        while (c != '"')
        {
            if (c == '\\')
                c = iss.get();
            if (iss.gcount() == 0)
                throw LexerException(LexerExceptionType::UnexpectedEOF);
            last_token_string.push_back(c);
            c = iss.get();
        }
        return Token::String;
    }

    Token
    Lexer::read_number()
    {
        while (is_num(c))
        {
            last_token_string.push_back(c);
            c = iss.get();
        }
        if (is_blank(c))
            return convert_number(Token::Integer);
        if (c == '.')
        {
            last_token_string.push_back('.');
            c = iss.get();
            while (c > '0' && c < '9')
            {
                last_token_string.push_back(c);
                c = iss.get();
            }
        }
        if (is_blank(c))
            return convert_number(Token::Floating);

        throw (LexerException(LexerExceptionType::UnexpectedSymbolAfterNumber));
    }

    Token
    Lexer::read_comment()
    {
        if (!last_token_string.empty())
            throw LexerException(LexerExceptionType::UnexpectedSymbolAfterLiteral);
        c = iss.get();
        while (c != '\n' && iss.gcount() != 0)
            c = iss.get();
        return Token::Comment;
    }

    Token
    Lexer::convert_number(Token type)
    {
        assert (type == Token::Floating || type == Token::Integer);
        if (type == Token::Floating)
            last_token_float = atof(last_token_string.c_str());
        if (type == Token::Integer)
            last_token_int = atoi(last_token_string.c_str());
        return type;
    }

    Token
    Lexer::get_token()
    {
        //Remove first blanks
        c = iss.get();
        while (is_blank(c))
            c = iss.get();

        last_token_string = "";
        last_token_int    = 0;
        last_token_float  = 0;

        while (true)
        {
            if (iss.gcount() == 0)
            {
                if (last_token_string.empty())
                    return Token::EndOfFile;
                return Token::Identifier;
            }
            switch (c)
            {
            case '"':
                return read_string();
            case ' ':
                if (last_token_string == "Kiu")
                    return Token::Extern;
                if (last_token_string == "Piou")
                    return Token::Define;
                if (last_token_string == "Coq")
                    return Token::EntryPoint;
                if (last_token_string == "Cot")
                    return Token::If;
                if (last_token_string == "cOt")
                    return Token::Then;
                if (last_token_string == "coT")
                    return Token::Else;
                if (last_token_string == "Glou")
                    return Token::StringType;
                if (last_token_string == "Kia")
                    return Token::IntegerType;
                if (last_token_string == "Pya")
                    return Token::FloatingType;
                return Token::Identifier;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                return read_number();
            case 'p':
            case 'i':
            case 'a':
            case 'o':
            case 'u':
            case 'k':
            case 'q':
            case 't':
            case 'y':
            case 'w':
            case 'c':
            case 'g':
            case 'l':
            case 'P':
            case 'I':
            case 'A':
            case 'O':
            case 'U':
            case 'K':
            case 'Q':
            case 'T':
            case 'Y':
            case 'W':
            case 'C':
            case 'G':
            case 'L':
                last_token_string.push_back(c);
                break;
            case '<':
                return check(Token::StartArg);
            case ';':
                return read_comment();
            case '>':
                return check(Token::EndArg);
            case ',':
                return check(Token::ArgSep);
            case '[':
                return check(Token::StartContent);
            case ']':
                return check(Token::EndContent);
            case '(':
                return check(Token::OpenParenthesis);
            case ')':
                return check(Token::CloseParenthesis);
            case ':':
                return check(Token::EndInstr);
            case '~':
                return check(Token::Affect);
            case '+':
                return check(Token::Plus);
            case '-':
                return check(Token::Minus);
            case '*':
                return check(Token::Mult);
            case '/':
                return check(Token::Div);
            case '{':
                return check(Token::Lt);
            case '}':
                return check(Token::Gt);
            case '?':
                return check(Token::Equal);
            case '$':
                return check(Token::Negate);
            default:
                throw LexerException(LexerExceptionType::InvalidCharacter);
            }
            c = iss.get();
        }

        return Token::Unknown;
    }
};
