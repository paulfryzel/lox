cmake_minimum_required(VERSION 3.23)
project(lox)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
add_executable(lox
        "examples/main.cpp"
        "src/driver/lox.h"
        "src/driver/lox.cpp"
        "src/scanner/token_type.h"
        "src/scanner/token.h"
        "src/scanner/token.cpp"
        "src/scanner/scanner.h"
        "src/scanner/scanner.cpp")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
