#include "scanner/token.h"

#include <ostream>
#include <string>

auto operator<<(std::ostream& out, const Token& token) -> std::ostream& {
  out << '[' << static_cast<int>(token.type_) << ' ' << token.lexeme_ << ' '
      << token.line_ << ']';
  return out;
}
