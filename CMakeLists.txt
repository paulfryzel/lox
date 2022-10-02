cmake_minimum_required(VERSION 3.23)
project(lox)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
add_executable(lox
  "examples/main.cpp"
  "src/lox.h"
  "src/lox.cpp"
  "src/token_type.h"
  "src/token.h"
  "src/token.cpp"
  "src/scanner.h"
  "src/scanner.cpp")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
