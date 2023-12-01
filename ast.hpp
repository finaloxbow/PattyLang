#ifndef AST_HPP
#define AST_HPP

#include <cstdint>
#include <iostream>
#include <sstream>
#include "lexer.hpp"

class Expr {
public:
    virtual std::string stringify() = 0;
};

class Lit : public Expr {
public:
    int64_t val;

    Lit(int64_t val) : val(val) {}

    std::string stringify(){
        std::string repr = "";
        repr += "Lit(";
        repr += std::to_string(val);
        repr += ")";

        return repr;
    }
};

class Prim1 : public Expr {
public:
    TokenType op_type;
    Expr* expr;

    Prim1(TokenType op_type, Expr* expr) : op_type(op_type), expr(expr) {}

    std::string stringify(){
        std::stringstream repr;
        repr << "Prim1(" << op_type << ", " << expr->stringify() << ")";

        return repr.str();
    }
};

#endif