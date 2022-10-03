#include <string>
#include <vector>

#include "driver/lox.h"

int main(int argc, char **argv) {
  const std::vector<std::string> arguments(argv + 1, argv + argc);
  Lox::Main(arguments);

  return 0;
}
