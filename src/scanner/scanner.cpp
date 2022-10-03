#include "scanner/scanner.h"

#include <vector>

#include "driver/lox.h"
#include "scanner/token_type.h"

std::unordered_map<std::string, TokenType> Scanner::keywords(
    {{"and", AND},
     {"class", CLASS},
     {"else", ELSE},
     {"false", FALSE},
     {"for", FOR},
     {"fun", FUN},
     {"if", IF},
     {"nil", NIL},
     {"or", OR},
     {"print", PRINT},
     {"return", RETURN},
     {"super", SUPER},
     {"this", THIS},
     {"true", TRUE},
     {"var", VAR},
     {"while", WHILE}});

std::vector<Token*> Scanner::ScanTokens() {
  while (!IsAtEnd()) {
    start_ = current_;
    ScanToken();
  }
  tokens_.push_back(new Token(END_OF_FILE, "", NULL, line_));
  return tokens_;
}

bool Scanner::IsAtEnd() const {
  return current_ >= static_cast<const int>(source_.length());
}

bool Scanner::IsDigit(const char c) { return c >= '0' && c <= '9'; }

bool Scanner::IsAlpha(const char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::IsAlphaNumeric(const char c) { return IsAlpha(c) || IsDigit(c); }

bool Scanner::Match(const char expected) {
  if (IsAtEnd()) {
    return false;
  }
  if (source_.at(current_) != expected) {
    return false;
  }
  current_++;
  return true;
}

char Scanner::Peek() const {
  if (IsAtEnd()) {
    return '\0';
  }
  return source_.at(current_);
}

char Scanner::PeekNext() const {
  if (current_ + 1 >= static_cast<int>(source_.length())) {
    return '\0';
  }
  return source_.at(current_ + 1);
}

void Scanner::ScanToken() {
  switch (const char c = Advance()) {
    case '(':
      AddToken(LEFT_PAREN);
      break;
    case ')':
      AddToken(RIGHT_PAREN);
      break;
    case '{':
      AddToken(LEFT_BRACE);
      break;
    case '}':
      AddToken(RIGHT_BRACE);
      break;
    case ',':
      AddToken(COMMA);
      break;
    case '.':
      AddToken(DOT);
      break;
    case '-':
      AddToken(MINUS);
      break;
    case '+':
      AddToken(PLUS);
      break;
    case ';':
      AddToken(SEMICOLON);
      break;
    case '*':
      AddToken(STAR);
      break;
    case '!':
      AddToken(Match('=') ? BANG_EQUAL : BANG);
      break;
    case '=':
      AddToken(Match('=') ? EQUAL_EQUAL : EQUAL);
      break;
    case '<':
      AddToken(Match('=') ? LESS_EQUAL : LESS);
      break;
    case '>':
      AddToken(Match('=') ? GREATER_EQUAL : GREATER);
      break;
    case '/':
      if (Match('/')) {
        // A comment goes until the end of the line.
        while (Peek() != '\n' && !IsAtEnd()) {
          Advance();
        }
      } else {
        AddToken(SLASH);
      }
      break;
    case ' ':
    case '\r':
    case '\t':
      // Ignore whitespace.
      break;
    case '\n':
      line_++;
      break;
    case '"':
      String();
      break;
    default:
      if (IsDigit(c)) {
        Number();
      } else if (IsAlpha(c)) {
        Identifier();
      } else {
        Lox::Error(line_, "Unexpected character.");
      }

      break;
  }
}

void Scanner::Identifier() {
  while (IsAlphaNumeric(Peek())) {
    Advance();
  }
  const std::string text = source_.substr(start_, current_ - start_);
  TokenType type = keywords.contains(text) ? keywords[text] : IDENTIFIER;
  AddToken(type);
}

void Scanner::String() {
  while (Peek() != '"' && !IsAtEnd()) {
    if (Peek() == '\n') {
      line_++;
    }
    Advance();
  }

  if (IsAtEnd()) {
    Lox::Error(line_, "Unterminated string.");
    return;
  }

  // The closing RIGHT_PAREN (").
  Advance();

  // Trim the surrounding quotes.
  std::string value = source_.substr(start_ + 1, current_ - start_ - 1);
  AddToken(STRING, value);
}

void Scanner::Number() {
  while (IsDigit(Peek())) {
    Advance();
  }

  // Look for a fractional part.
  if (Peek() == '.' && IsDigit(PeekNext())) {
    // Consume the "."
    Advance();

    while (IsDigit(Peek())) {
      Advance();
    }
  }

  AddToken(NUMBER, std::stod(source_.substr(start_, current_ - start_)));
}

char Scanner::Advance() { return source_.at(current_++); }

void Scanner::AddToken(const TokenType& type) { AddToken(type, NULL); }

void Scanner::AddToken(const TokenType& type, const std::any& literal) {
  const auto text = source_.substr(start_, current_ - start_);
  tokens_.push_back(new Token(type, text, literal, line_));
}
