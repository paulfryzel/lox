#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string_view>
#include <sstream>

void run_file(char *filename);
void run_prompt();
void run(std::string_view source);

int main(int argc, char *argv[]) {
  if (argc > 2) {
    std::cout << "Usage: lox [script]" << '\n';
    std::exit(64); // UNIX's sysexits.h convention
  } else if (argc == 2) {
    run_file(argv[1]);
  } else {
    run_prompt();
  }

  return 0;
}
void run_file(char *filename) {
  std::ifstream in(filename, std::ios::in | std::ios::binary);

  if (in) {
    std::ostringstream contents;
    contents << in.rdbuf();
    in.close();
    run(contents.str());
  }
}

void run_prompt() {
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
}

void run(const std::string_view source) {
  std::cout << source << '\n';
}
