#ifndef AST_HPP
#define AST_HPP

#include <cstdint>
#include <iostream>

class Expr {
public:
    virtual std::string stringify() = 0;
};

class Lit : public Expr {
public:
    int64_t val;

    Lit(int64_t val){ this->val = val; }

    std::string stringify(){
        std::string repr = "";
        repr += "Lit(";
        repr += std::to_string(val);
        repr += ")";

        return repr;
    }
};

#endif