#include <string>
#include <vector>

#include "driver/lox.h"

auto main(int argc, char** argv) -> int {
  const std::vector<std::string> arguments(argv + 1, argv + argc);
  Lox::Main(arguments);

  return 0;
}
