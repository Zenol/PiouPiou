#include "Token.hpp"

namespace PiouC
{
    std::ostream& operator<< (std::ostream &out, Token token)
    {
        switch (token)
        {
        case Token::Define:
            out << "Define";
            break;
        case Token::StartArg:
            out << "StartArg";
            break;
        case Token::EndArg:
            out << "EndArg";
            break;
        case Token::Extern:
            out << "Extern";
            break;
        case Token::StartContent:
            out << "StartContent";
            break;
        case Token::EndContent:
            out << "EndContent";
            break;
        case Token::EndInstr:
            out << "EndInstr";
            break;
        case Token::Identifier:
            out << "Identifier";
            break;
        case Token::Floating:
            out << "Floating";
            break;
        case Token::Integer:
            out << "Integer";
            break;
        case Token::String:
            out << "String";
            break;
        case Token::EntryPoint:
            out << "EntryPoint";
            break;
        case Token::Comment:
            out << "Comment";
            break;
        case Token::Unknown:
            out << "Unknown";
            break;
        case Token::EndOfFile:
            out << "EndOfFile";
            break;
        case Token::If:
            out << "If";
            break;
        case Token::Then:
            out << "Then";
            break;
        case Token::Else:
            out << "Else";
            break;
        case Token::Plus:
            out << "Plus";
            break;
        case Token::Minus:
            out << "Minus";
            break;
        case Token::Mult:
            out << "Mult";
            break;
        case Token::Div:
            out << "Div";
            break;
        case Token::Lt:
            out << "Lt";
            break;
        case Token::Gt:
            out << "Gt";
            break;
        case Token::Affect:
            out << "Affect";
            break;
        case Token::StringType:
            out << "StringType";
            break;
        case Token::FloatingType:
            out << "FloatingType";
            break;
        case Token::IntegerType:
            out << "IntegerType";
            break;
        case Token::Equal:
            out << "Equal";
            break;
        case Token::Negate:
            out << "Negate";
            break;
        case Token::OpenParenthesis:
            out << "OpenParenthesis";
            break;
        case Token::CloseParenthesis:
            out << "CloseParenthesis";
            break;
        case Token::ArgSep:
            out << "ArgSep";
            break;
        default:
            out << "??:" << static_cast<int>(token);
        }
    }
}
