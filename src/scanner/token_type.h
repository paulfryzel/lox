#ifndef LOX_TOKEN_TYPE_H
#define LOX_TOKEN_TYPE_H

enum class TokenType {
  // Single-character tokens.
  LEFT_PAREN,  // 0
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR, // 10

  // One or two character tokens.
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL, // 18

  // Literals.
  IDENTIFIER,
  STRING,
  NUMBER, // 21

  // Keywords.
  AND,
  CLASS,
  ELSE,
  FALSE,
  FUN,
  FOR,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE, // 37

  END_OF_FILE // 38
};

#endif  // LOX_TOKEN_TYPE_H
