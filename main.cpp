#include <string>
#include <iostream>
#include "lexer.hpp"

int main(){
    
    std::string filepath = "./test.ptl";
    Lexer lexer(filepath);

    while(!lexer.empty())
        std::cout << lexer.consume_next() << "\n";

    return 0;
}