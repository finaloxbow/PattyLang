#include "lexer.hpp"

#include <sstream>
#include <fstream>
#include <vector>
#include <regex>

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
    {regex("^([^])", std::regex::extended), TokenType::carat},
    {regex("^([\\)])", std::regex::extended), TokenType::close_paren},
    {regex("^([\\]])", std::regex::extended), TokenType::close_square},
    {regex("^([:])", std::regex::extended), TokenType::colon},
    {regex("^([.])", std::regex::extended), TokenType::dot},
    {regex("^([=])", std::regex::extended), TokenType::equals},
    {regex("^([-])", std::regex::extended), TokenType::minus},
    {regex("^([\\(])", std::regex::extended), TokenType::open_paren},
    {regex("^([\\[])", std::regex::extended), TokenType::open_square},
    {regex("^([+])", std::regex::extended), TokenType::plus},
    {regex("^([;])", std::regex::extended), TokenType::semicolon},
    {regex("^([/])", std::regex::extended), TokenType::slash},
};

Token::Token(TokenType type, std::string data)
: type(type), data(data) {}

Token::Token(TokenType type, uint64_t data)
: type(type), data(data) {}

Lexer::Lexer(string &filepath)
{
    std::ifstream input_stream(filepath);
    std::stringstream buffer;
    buffer << input_stream.rdbuf();
    this->program = buffer.str();
}

Token Lexer::consume_next()
{
    //this is where matching happens
}
