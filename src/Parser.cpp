#include "Parser.hpp"
#include "ParserException.hpp"
#include <iostream>
namespace PiouC
{

    Parser::Parser(Lexer &lex)
        :lex(lex), current_tok(Token::Unknown)
    {
        //Read the first token
        get_next_token();
    }

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
    Parser::parse_floating_expr() noexcept
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
            throw ParserException(ParserExceptionType::ExpectedEndOfParenth);
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

        if (current_tok != Token::EndArg)
            while (true)
            {
                PExprAST expr = parse_expr();

                if (current_tok == Token::EndArg)
                    break;

                if (current_tok != Token::ArgSep)
                    throw ParserException(ParserExceptionType::ExpectedEndOfArg);
                get_next_token(); // eat ','
            }
        get_next_token(); // eat '>'

        return PExprAST(new CallExprAST(identifier, args));
    }

    PExprAST
    Parser::parse_primary()
    {
        switch(current_tok)
        {
        case Token::Identifier:
            return parse_identifier_expr();
        case Token::Integer:
            return parse_integer_expr();
        case Token::String:
            return parse_string_expr();
        case Token::Floating:
            return parse_floating_expr();
        case Token::OpenParenthesis:
            return parse_parenth_expr();
        default:
            throw ParserException(ParserExceptionType::ExpectedPrimaryExpr);
        }
    }

    PExprAST
    Parser::parse_binop_rhs(int precedence_min, PExprAST lhs)
    {
        // We will try to read operators and replace the
        // current lhs by a bigger one, until there is
        // no more tokens.
        while (true)
        {
            int token_precedence = get_token_precedence();

            // If it's not a binop or it's a binop with
            // lower precedence.
            if (token_precedence < precedence_min)
                return lhs;

            //We know it's a binop, so we read [op, prim]
            Token binop = current_tok;
            get_next_token(); // eat the binop
            PExprAST rhs = parse_primary();

            // If the next token have a stronger precedence,
            // we should compute it as belonging to rhs.
            int next_precedence = get_token_precedence();
            if (next_precedence > token_precedence)
                rhs = PExprAST(parse_binop_rhs(token_precedence + 1, rhs));

            //Otherwise, we replace the lhs by 'lhs, op, prim'
            lhs = PExprAST(new BinaryExprAST(binop, lhs, rhs));
        }
    }

    PExprAST
    Parser::parse_expr()
    {
        PExprAST lhs = parse_primary();
        return parse_binop_rhs(0, lhs);
    }

    PPrototypeAST
    Parser::parse_prototype()
    {
        Type return_type = get_type(current_tok);

        get_next_token(); // eat type token

        std::string name;
        //We should read identifier or entry point token
        if (current_tok == Token::Identifier)
        {
            name = lex.get_last_token_value<std::string>();
            get_next_token(); // eat identifier
        }
        else if (current_tok == Token::EntryPoint)
        {
            name = "Coq";
            get_next_token(); // eat identifier
        }
        else
            throw ParserException(ParserExceptionType::ExpectedIdentifier);

        if (current_tok != Token::StartArg)
            throw ParserException(ParserExceptionType::ExpectedStartArg);
        get_next_token(); // eat '<'

        //Read types of arguments
        ArgList args;
        if (current_tok != Token::EndArg)
            while (true)
            {
                if (!is_type(current_tok))
                    throw ParserException(ParserExceptionType::ExpectedType);

                Type arg_type = get_type(current_tok);
                get_next_token(); // eat type

                // Users are allowed to do not specify a name
                std::string arg_name;
                if (current_tok == Token::Identifier)
                {
                    name = lex.get_last_token_value<std::string>();
                    get_next_token();
                }

                args.push_back(ArgPair(arg_type, arg_name));

                if (current_tok == Token::EndArg)
                    break;

                if (current_tok != Token::ArgSep)
                    throw ParserException(ParserExceptionType::ExpectedEndOfArg);

                get_next_token(); //eat separator ','
        }
        get_next_token(); // eat '>'

        return PPrototypeAST(new PrototypeAST(return_type, name, args));
    }

    PExprAST
    Parser::parse_extern()
    {
        get_next_token(); // eat extern identifier

        if (current_tok != Token::String)
            throw ParserException(ParserExceptionType::ExpectedExternName);

        std::string extern_name = lex.get_last_token_value<std::string>();
        get_next_token(); // eat string

        //Read prototype
        PPrototypeAST prototype = parse_prototype();

        if (current_tok != Token::EndInstr)
            throw ParserException(ParserExceptionType::ExpectedEndOfInstr);
        get_next_token(); // eat ':'

        return PExprAST(new ExternAST(extern_name, prototype));
    }

    PExprAST
    Parser::parse_function()
    {
        get_next_token(); // eat the Define token

        PPrototypeAST prototype = parse_prototype();

        if (current_tok != Token::StartContent)
            throw ParserException(ParserExceptionType::ExpectedStartContent);
        get_next_token(); // eat '['

        InstList imp;
        while (current_tok != Token::EndContent)
        {
            PExprAST inst = parse_expr();

            if (current_tok != Token::EndInstr)
                throw ParserException(ParserExceptionType::ExpectedEndOfInstr);
            get_next_token(); // eat ':'

            imp.push_back(inst);
        }
        get_next_token(); // eat ']'

        return PExprAST(new FunctionAST(prototype, imp));
    }

    int
    Parser::get_token_precedence()
    {
        //Return the precedence of the current tokent
        switch(current_tok)
        {
        case Token::Mult:
            return 80;
        case Token::Div:
            return 70;
        case Token::Plus:
            return 60;
        case Token::Minus:
            return 60;
        case Token::Lt:
            return 40;
        case Token::Gt:
            return 40;
        case Token::Equal:
            return 30;
        case Token::Affect:
            return 20;
        default:
            //If it's not a binop
            return -1;
        }
    }

    PExprAST
    Parser::get_next_expression()
    {
        while (true)
        {
            //TODO Handle global variable

            //Top level prototype
            if (is_type(current_tok))
                return parse_prototype();

            switch(current_tok)
            {
            case Token::EndOfFile:
                return PExprAST(nullptr);
            case Token::EndInstr:
                //Ignore top level end of instr
                //And top level comments
                get_next_token();
                break;
            case Token::Define:
                return parse_function();
            case Token::Extern:
                return parse_extern();
            default:
                throw ParserException(ParserExceptionType::ExpectedTopLevel);
            }
        }
    }

    Token
    Parser::get_current_token() const noexcept
    {
        return current_tok;
    }

    Type
    get_type(const Token tok)
    {
        switch(tok)
        {
        case Token::StringType:
            return Type::String;
        case Token::FloatingType:
            return Type::Floating;
        case Token::IntegerType:
            return Type::Integer;
        default:
            throw ParserException(ParserExceptionType::UnknowType);
        }
    }
}
