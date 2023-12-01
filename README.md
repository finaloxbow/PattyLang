Writing a Compiler for PattyLang, a language with Rust-like syntax (because I LOVE RUST).

Program = list(Expr)
Expr = Lit(int)
    | Prim1(op, Expr)
    | (If(Expr, Expr, Expr))