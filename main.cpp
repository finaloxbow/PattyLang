#include "lexer.hpp"
#include "parse.hpp"
#include "ast.hpp"

int main(){
    std::string filepath = "./test.ptl";
    Lexer lexer(filepath);

    auto tokens = lexer.tokenize_program();

    for(auto tok : tokens) std::cout << tok << "\n";

    Expr* program = Parser::parse_tokens(tokens);

    std::cout << program->stringify() << "\n";

    return 0;
}