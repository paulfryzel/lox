#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "lox.h"

void Lox::main(std::vector<std::string> &args) {
  if (args.size() > 1) {
    std::cout << "Usage: lox [script]" << '\n';
    std::exit(64); // UNIX's sysexits.h convention
  } else if (args.size() == 1) {
    run_file(args[0]);
  } else {
    run_prompt();
  }
}

void Lox::error(int line, std::string_view message) {
  report(line, "", message);
  had_error_ = true;
}

bool Lox::had_error_ = false;

void Lox::run_file(const std::string &filename) {
  std::ifstream in(filename, std::ios::in | std::ios::binary);

  if (in) {
    std::ostringstream contents;
    contents << in.rdbuf();
    in.close();
    run(contents.str());

    // Indicate an error in the exit code.
    if (had_error_) {
      std::exit(65);
    }
  }
}

void Lox::run_prompt() {
  std::string line, lines;

  std::cout << "> ";

  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      break;
    }
    std::cout << "> ";
    lines.append(line);
  }
  run(lines);
  had_error_ = false;
}

void Lox::run(std::string_view source) {
  std::cout << source << '\n';
}

void Lox::report(int line,
                 std::string_view where,
                 std::string_view message) {
  std::cerr << "[line " << line << "] Error" << where << ": " << message
            << '\n';
}
