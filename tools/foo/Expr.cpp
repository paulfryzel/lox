#include <vector>

struct Expr {
};

class Binary : Expr {
  Binary(Expr left, Token operator, Expr right) {}
};

class Grouping : Expr {
  Grouping(Expr expression) {}
};

class Literal : Expr {
  Literal(Object value) {}
};

class Unary : Expr {
  Unary(Token operator, Expr right) {}
};

