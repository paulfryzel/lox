#ifndef LOX_SCANNER_H
#define LOX_SCANNER_H

#include <any>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "scanner/token.h"

class Scanner {
 public:
  explicit Scanner(std::string source) : source_(std::move(source)) {}

  auto ScanTokens() -> std::vector<Token>;

 private:
  auto IsAtEnd() const -> bool;
  static auto IsDigit(char c) -> bool;
  static auto IsAlpha(char c) -> bool;
  static auto IsAlphaNumeric(char c) -> bool;
  auto ScanToken() -> void;
  auto Identifier() -> void;
  auto String() -> void;
  auto Number() -> void;
  auto Advance() -> char;
  auto Match(char expected) -> bool;
  auto Peek() const -> char;
  auto PeekNext() const -> char;
  auto AddToken(const TokenType& type) -> void;
  auto AddToken(const TokenType& type, const std::any& literal) -> void;

  std::string source_;
  std::vector<Token> tokens_;

  int start_ = 0;
  int current_ = 0;
  int line_ = 1;

  static std::unordered_map<std::string, TokenType> keywords;
};

#endif  // LOX_SCANNER_H
