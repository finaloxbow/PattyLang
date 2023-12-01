#ifndef PARSER_HPP
#define PARSER_HPP

#include <memory>
#include <string>
#include <vector>
#include "lexer.hpp"
#include "ast.hpp"

//given tokens, parse into list of expressions
class Parser {
private:
    std::unique_ptr<Lexer> lexer;
public:
    Parser(std::string& filepath);
    
    Token eat_token(TokenType type);
    Expr* parse_expr();
    std::vector<Expr*> parse_program();
};

#endif