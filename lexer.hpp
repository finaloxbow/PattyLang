#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <regex>

#include "ast.hpp"

using std::string;
using std::vector;

class Lexer {
public:

    enum TokenType {
        TOK_INT64,
    };

    //Token with optional data
    struct Token{
        
        TokenType type;

        union Data {
            uint64_t val;
        } data;

        static Token construct_token(TokenType type, string& data);

        friend std::ostream& operator<<(std::ostream& os, const Token& tok);

    };

    Lexer(string& file_path);

    vector<Token> tokenize_program();

private:
    string program;
    vector<std::pair<std::regex, TokenType>> regexes;
};