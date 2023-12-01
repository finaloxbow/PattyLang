#include "parser.hpp"

#include <stdexcept>

Parser::Parser(std::string& filepath)
: lexer(std::make_unique<Lexer>(filepath)) {}

Token Parser::eat_token(TokenType type){
    Token tok = lexer->consume_next();

    if(type == TokenType::DEFAULT || type == tok.type)
        return tok;
    else
        throw std::runtime_error("Parsing error. Consuming token different from expected.");
}

Expr* Parser::parse_expr(){
    Token token = eat_token(TokenType::DEFAULT);
    
    switch(token.type){
        case TokenType::uint64:
            return new Lit(std::get<uint64_t>(token.data));
        case TokenType::plus:
        case TokenType::minus:
            {
                Expr* rest_expr = parse_expr();
                return new Prim1(token.type, rest_expr);
            }
        default:
            break;
    }

    throw new std::runtime_error("Parsing error. Tokens did not match a valid expr.");
}

std::vector<Expr*> Parser::parse_program(){
    std::vector<Expr*> program;

    while(!lexer->empty()){
        program.push_back(parse_expr());
    }

    return program;
}