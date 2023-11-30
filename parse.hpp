#ifndef PARSE_HPP
#define PARSE_HPP

#include <vector>

#include "ast.hpp"
#include "lexer.hpp"

class Parser {
public:
    static Expr* parse_tokens(std::vector<Lexer::Token> tokens);
};

#endif