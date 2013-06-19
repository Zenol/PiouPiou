#include "Parser.hpp"
#include "ParserException.hpp"

namespace PiouC
{

    Parser::Parser(Lexer &lex)
        :lex(lex), current_tok(Token::Unknown)
    {}

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
            throw ParserException(ParserExceptionType::ExpectedEndOfInstr);
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
        while (current_tok != Token::EndArg)
        {
            PExprAST expr = parse_expr();
            if (current_tok != Token::ArgSep && current_tok != Token::EndArg)
                throw ParserException(ParserExceptionType::ExpectedEndOfArg);
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

    PExprAST
    Parser::parse_prototype()
    {
        Type return_type = get_type(current_tok);

        get_next_token(); //eat type token

        if (current_tok != Token::Identifier)
            throw ParserException(ParserExceptionType::ExpectedIdentifier);

        std::string name = lex.get_last_token_value<std::string>();
        get_next_token(); //eat identifier

        if (current_tok != Token::StartArg)
            throw ParserException(ParserExceptionType::ExpectedStartArg);

        //Read types of arguments
        std::vector<Type> args;
        while (current_tok != Token::EndArg)
        {
            if (!is_type(current_tok))
                throw ParserException(ParserExceptionType::ExpectedType);

            args.push_back(get_type(current_tok));

            // We allow users to write a name after a type,
            // althought it's not required.
            if (current_tok == Token::Identifier)
                get_next_token();
        }

        return PExprAST(new PrototypeAST(return_type, name, args));
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
        default:
            //If it's not a binop
            return -1;
        }
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
