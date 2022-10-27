#include "driver/lox.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <utility>
#include <vector>

#include "scanner/scanner.h"
#include "scanner/token.h"

auto Lox::Main(const std::vector<std::string>& args) -> void {
  if (args.size() > 1) {
    std::cout << "Usage: lox [script]" << '\n';
    std::exit(64);  // UNIX's sysexits.h convention
  } else if (args.size() == 1) {
    RunFile(args[0]);
  } else {
    RunPrompt();
  }
}

auto Lox::Error(int line, std::string_view message) -> void {
  Report(line, "", message);
  had_error = true;
}

bool Lox::had_error = false;

auto Lox::RunFile(const std::string& filename) -> void {
  std::ifstream in(filename, std::ios::in | std::ios::binary);

  if (in) {
    std::ostringstream contents;
    contents << in.rdbuf();
    in.close();
    Run(contents.str());

    // Indicate an error in the exit code.
    if (had_error) {
      std::exit(65);
    }
  }
}

auto Lox::RunPrompt() -> void {
  std::string line;
  std::string lines;

  std::cout << "> ";

  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      break;
    }
    std::cout << "> ";
    lines.append(line);
  }
  Run(lines);
  had_error = false;
}

auto Lox::Run(std::string source) -> void {
  auto scanner = std::make_unique<Scanner>(std::move(source));

  for (const auto& token : scanner->ScanTokens()) {
    std::cout << token << ' ';
  }
}

auto Lox::Report(int line, std::string_view where, std::string_view message)
    -> void {
  std::cerr << "\n[line " << line << "] Error" << where << ": " << message
            << '\n';
}
