#include "parse.hpp"

#include <iostream>

static Expr* parse_tokens_helper(std::vector<Lexer::Token> tokens, int& idx);

Expr* Parser::parse_tokens(std::vector<Lexer::Token> tokens){
    int idx = 0;
    auto ans = parse_tokens_helper(tokens, idx);
    
    if(idx < tokens.size())
        throw std::runtime_error("Too many tokens.");
    
    return ans;
}

static Expr* parse_tokens_helper(std::vector<Lexer::Token> tokens, int& idx){
    switch(tokens[idx].type){
        case Lexer::TokenType::TOK_INT64:
            return new Lit(tokens[idx++].data.val);
            break;
        default:
            throw std::runtime_error("Parsing failed in parse_tokens_helper().");
            break;
    }

    throw std::runtime_error("Parsing failed.");
}