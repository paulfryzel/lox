#include "scanner/token.h"

#include <ostream>
#include <string>

std::ostream& operator<<(std::ostream& out, const Token& token) {
  out << '[' << static_cast<int>(token.type_) << ' ' << token.lexeme_ << ' '
      << token.line_ << ']';
  return out;
}
