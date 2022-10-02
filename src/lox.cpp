#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "lox.h"
#include "scanner.h"
#include "token.h"

void Lox::Main(const std::vector<std::string>& args) {
  if (args.size() > 1) {
    std::cout << "Usage: lox [script]" << '\n';
    std::quick_exit(64);  // UNIX's sysexits.h convention
  } else if (args.size() == 1) {
    RunFile(args[0]);
  } else {
    RunPrompt();
  }
}

void Lox::Error(int line, std::string_view message) {
  Report(line, "", message);
  had_error_ = true;
}

bool Lox::had_error_ = false;

void Lox::RunFile(const std::string& filename) {
  std::ifstream in(filename, std::ios::in | std::ios::binary);

  if (in) {
    std::ostringstream contents;
    contents << in.rdbuf();
    in.close();
    Run(contents.str());

    // Indicate an error in the exit code.
    if (had_error_) {
      std::quick_exit(65);
    }
  }
}

void Lox::RunPrompt() {
  std::string line, lines;

  std::cout << "> ";

  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      break;
    }
    std::cout << "> ";
    lines.append(line);
  }
  Run(lines);
  had_error_ = false;
}

void Lox::Run(const std::string& source) {
  const auto scanner = new Scanner(source);

  for (const auto& token : scanner->ScanTokens()) {
    std::cout << *token << ' ';
  }
}

void Lox::Report(int line, std::string_view where, std::string_view message) {
  std::cerr << "[line " << line << "] Error" << where << ": " << message
            << '\n';
}
