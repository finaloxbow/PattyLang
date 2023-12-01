#include <variant>
#include <string>

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
    end,
    equals,
    minus,
    open_paren,
    open_square,
    plus,
    semicolon,
    slash,
};

struct Token {
    TokenType type;
    std::variant<std::string, uint64_t> data;

    Token(TokenType type, std::string data);
    Token(TokenType type, uint64_t data);
};

class Lexer {
private:
    std::string program;
public:
    Lexer(std::string& filepath);

    Token consume_next();
};

#endif