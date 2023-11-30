#include "lexer.hpp"

int main(){
    std::string filepath = "./test.ptl";
    Lexer lexer(filepath);

    auto tokens = lexer.tokenize_program();

    for(auto tok : tokens) std::cout << tok << "\n";

    return 0;
}