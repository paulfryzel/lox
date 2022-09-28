#include <string>
#include <vector>

#include "lox.h"

auto main(int argc, char **argv) -> int {
  std::vector<std::string> arguments(argv + 1, argv + argc);
  Lox::main(arguments);

  return 0;
}
