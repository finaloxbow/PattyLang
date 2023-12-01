#include <string>
#include <iostream>
#include "parser.hpp"

int main(){
    
    std::string filepath = "./test.ptl";
    Parser parser(filepath);

    std::vector<Expr*> program = parser.parse_program();

    for(auto expr : program)
        std::cout << expr->stringify() << "\n";

    return 0;
}