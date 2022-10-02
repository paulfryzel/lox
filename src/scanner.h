#ifndef LOX_SCANNER_H
#define LOX_SCANNER_H

#include <any>
#include <unordered_map>
#include <string>
#include <vector>

#include "token.h"

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
  [[nodiscard]] bool IsAtEnd() const;
  [[nodiscard]] static bool IsDigit(char c);
  [[nodiscard]] static bool IsAlpha(char c);
  [[nodiscard]] static bool IsAlphaNumeric(char c);
  void ScanToken();
  void Identifier();
  void String();
  void Number();
  char Advance();
  bool Match(char expected);
  [[nodiscard]] char Peek() const;
  [[nodiscard]] char PeekNext() const;
  void AddToken(const TokenType& type);
  void AddToken(const TokenType& type, const std::any& literal);

  const std::string& source_;
  std::vector<Token*> tokens_;

  int start_ = 0;
  int current_ = 0;
  int line_ = 1;

  static std::unordered_map<std::string, TokenType> keywords_;
};

#endif  // LOX_SCANNER_H
