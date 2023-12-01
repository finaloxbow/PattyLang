#include "lexer.hpp"

#include <sstream>
#include <fstream>
#include <vector>
#include <regex>
#include <cctype>
#include <stdexcept>

using std::vector;
using std::regex;
using std::pair;
using std::string;

vector<pair<regex, TokenType>> regexes
{
    {regex("^([0-9]+)", std::regex::extended), TokenType::uint64},
    {regex("^([a-zA-Z]+)", std::regex::extended), TokenType::id},
    {regex("^\"([a-zA-Z]*)\"", std::regex::extended), TokenType::quoted_str},
    {regex("^([*])", std::regex::extended), TokenType::asterisk},
    {regex("^([@])", std::regex::extended), TokenType::at},
    {regex("^([\\^])", std::regex::extended), TokenType::carat},
    {regex("^([\\)])", std::regex::extended), TokenType::close_paren},
    {regex("^(\\])", std::regex::extended), TokenType::close_square},
    {regex("^([:])", std::regex::extended), TokenType::colon},
    {regex("^([.])", std::regex::extended), TokenType::dot},
    {regex("^([=])", std::regex::extended), TokenType::equals},
    {regex("^([-])", std::regex::extended), TokenType::minus},
    {regex("^([\\(])", std::regex::extended), TokenType::open_paren},
    {regex("^(\\[)", std::regex::extended), TokenType::open_square},
    {regex("^([+])", std::regex::extended), TokenType::plus},
    {regex("^([;])", std::regex::extended), TokenType::semicolon},
    {regex("^([/])", std::regex::extended), TokenType::slash},
    {regex("^(\\{)", std::regex::extended), TokenType::open_curly},
    {regex("^(\\})", std::regex::extended), TokenType::close_curly},
};

Token::Token(TokenType type, std::string data)
: type(type), data(data) {}

Token::Token(TokenType type, uint64_t data)
: type(type), data(data) {}

std::ostream& operator<<(std::ostream& os, const Token& token){
    switch(token.type){
        case TokenType::uint64:
            os << "uint64";
            break;
        case TokenType::id:
            os << "id";
            break;
        case TokenType::quoted_str:
            os << "quoted_str";
            break;
        case TokenType::asterisk:
            os << "asterisk";
            break;
        case TokenType::at:
            os << "at";
            break;
        case TokenType::carat:
            os << "carat";
            break;
        case TokenType::close_paren:
            os << "close_paren";
            break;
        case TokenType::close_square:
            os << "close_square";
            break;
        case TokenType::colon:
            os << "colon";
            break;
        case TokenType::dot:
            os << "dot";
            break;
        case TokenType::equals:
            os << "equals";
            break;
        case TokenType::minus:
            os << "minus";
            break;
        case TokenType::open_paren:
            os << "open_paren";
            break;
        case TokenType::open_square:
            os << "open_square";
            break;
        case TokenType::plus:
            os << "plus";
            break;
        case TokenType::semicolon:
            os << "semicolon";
            break;
        case TokenType::slash:
            os << "slash";
            break;
        case TokenType::open_curly:
            os << "open_curly";
            break;
        case TokenType::close_curly:
            os << "closed_curly";
            break;
        default:
            throw std::runtime_error("Printing token failed. Probably missed an enum in the switch.");
            break;
    }

    if(token.type == TokenType::uint64){
        if(std::holds_alternative<uint64_t>(token.data))
            os << "(" << std::get<uint64_t>(token.data) << ")"; 
        else
            throw std::runtime_error("Token is uint64 but holds a string");
    }
    else if(token.type == TokenType::id || token.type == TokenType::quoted_str){
        if(std::holds_alternative<string>(token.data))
            os << "(" << std::get<string>(token.data) << ")";
        else
            throw std::runtime_error("Token is string but holds a uint64");
    }

    return os;
}

Lexer::Lexer(string &filepath)
{
    std::ifstream input_stream(filepath);
    std::stringstream buffer;
    buffer << input_stream.rdbuf();
    this->program = buffer.str();
}

bool Lexer::empty()
{
    return program == "";
}

void Lexer::skip_whitespace()
{
    int idx = 0;
    while(idx < program.size() && std::isspace(program[idx])) idx++;

    program = program.substr(idx);
}

Token Lexer::consume_next()
{
    skip_whitespace();

    if(empty())
        throw std::runtime_error("No tokens left");
    
    std::smatch matches;
    for(int i = 0; i < regexes.size(); i++){
        if(std::regex_search(program, matches, regexes[i].first)){
            string result = matches[1].str();
            program = matches.suffix().str();

            if(regexes[i].second == TokenType::uint64)
                return Token(regexes[i].second, std::stol(result));
            else
                return Token(regexes[i].second, result);
        }
    }

    throw std::runtime_error("Reading next token failed");
}
