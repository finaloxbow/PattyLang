#include <variant>
#include <string>
#include <iostream>

#ifndef LEXER_HPP
#define LEXER_HPP

enum class TokenType {
    uint64,
    id,
    quoted_str,
    asterisk,
    at,
    carat,
    close_paren,
    close_square,
    colon,
    dot,
    equals,
    minus,
    open_paren,
    open_square,
    plus,
    semicolon,
    slash,
    open_curly,
    close_curly,
    DEFAULT,
};

std::ostream& operator<<(std::ostream& os, const TokenType& token);

struct Token {
    TokenType type;
    std::variant<std::string, uint64_t> data;

    Token(TokenType type, std::string data);
    Token(TokenType type, uint64_t data);

    friend std::ostream& operator<<(std::ostream& os, const Token& token);
};

class Lexer {
private:
    std::string program;
public:
    Lexer(std::string& filepath);

    bool empty();
    void skip_whitespace();
    Token consume_next();
};

#endif