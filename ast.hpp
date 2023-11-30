#include <cstdint>

class Expr {};

class Lit : public Expr {
public:
    int64_t val;
};