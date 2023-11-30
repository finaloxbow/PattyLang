#include "lexer.hpp"

#include <fstream>
#include <sstream>
#include <regex>
#include <stdexcept>

Lexer::Lexer(string& file_path){
    std::ifstream input_stream(file_path);
    std::stringstream buffer;
    buffer << input_stream.rdbuf();

    program = buffer.str();

    regexes.push_back({std::regex("^(-?[0-9]+)[ ]*", std::regex::extended), TokenType::TOK_INT64});
}

vector<Lexer::Token> Lexer::tokenize_program()
{
    program = std::regex_replace(program, std::regex("\n"), " ");
    
    vector<Token> tokens;

    while(program.size() > 0){
        std::smatch matches;
        bool matched = false;

        for(int i = 0; i < regexes.size(); i++){
            if(std::regex_search(program, matches, regexes[i].first)){
                string data = matches[1].str();
                tokens.push_back(Token::construct_token(regexes[i].second, data));
                program = matches.suffix().str();
                matched = true;
                break;
            }
        }

        if(!matched)
            throw std::runtime_error("Invalid syntax detected.");
    }
    
    return tokens;
}

Lexer::Token Lexer::Token::construct_token(TokenType type, string &data)
{
    Token tok;
    tok.type = type;

    switch(type){
        case TOK_INT64:
            tok.data.val = std::stol(data);
            break;
        default:
            throw std::invalid_argument("Invalid token type.");
            break;
    }

    return tok;
}

std::ostream& operator<<(std::ostream& os, const Lexer::Token& tok){
    switch(tok.type){
        case Lexer::TokenType::TOK_INT64:
            os << "TOK_INT64(" << tok.data.val << ")";
            break;
        default:
            os << "INVALID_TOK";
            break;
    }
    
    return os;
}
