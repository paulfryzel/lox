#ifndef LOX_TOKEN_H
#define LOX_TOKEN_H

#include <any>
#include <ostream>
#include <string>
#include <utility>

#include "scanner/token_type.h"

class Token {
 public:
  Token(TokenType type, std::string lexeme, std::any literal, int line)
      : type_(type),
        lexeme_(std::move(lexeme)),
        literal_(std::move(literal)),
        line_(line) {}

  friend auto operator<<(std::ostream& out, const Token& token)
      -> std::ostream&;

 private:
  TokenType type_;
  std::string lexeme_;
  std::any literal_;
  int line_;
};

#endif  // LOX_TOKEN_H
