#include "scanner/token.h"

#include <ostream>
#include <string>

std::ostream& operator<<(std::ostream& out, const Token& token) {
  // return "<type_>" + ' ' + lexeme_ + ' ' + "<literal_>";
  out << '[' << token.type_ << ' ' << token.lexeme_ << ' ' << token.line_
      << ']';
  return out;
}
