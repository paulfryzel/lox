#ifndef LOX_SCANNER_H
#define LOX_SCANNER_H

#include <any>
#include <string>
#include <unordered_map>
#include <vector>

#include "scanner/token.h"

class Scanner {
 public:
  explicit Scanner(const std::string& source) : source_(source) {}

  ~Scanner() {
    for (const auto token : tokens_) {
      delete token;
    }
  }

  std::vector<Token*> ScanTokens();

 private:
  bool IsAtEnd() const;
  static bool IsDigit(char c);
  static bool IsAlpha(char c);
  static bool IsAlphaNumeric(char c);
  void ScanToken();
  void Identifier();
  void String();
  void Number();
  char Advance();
  bool Match(char expected);
  char Peek() const;
  char PeekNext() const;
  void AddToken(const TokenType& type);
  void AddToken(const TokenType& type, const std::any& literal);

  const std::string& source_;
  std::vector<Token*> tokens_;

  int start_ = 0;
  int current_ = 0;
  int line_ = 1;

  static std::unordered_map<std::string, TokenType> keywords;
};

#endif  // LOX_SCANNER_H
