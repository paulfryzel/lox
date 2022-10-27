#ifndef LOX_LOX_H
#define LOX_LOX_H

#include <string>
#include <string_view>
#include <vector>

class Lox {
 public:
  static auto Main(const std::vector<std::string>& args) -> void;
  static auto Error(int line, std::string_view message) -> void;

  static bool had_error;

 private:
  static auto RunFile(const std::string& filename) -> void;
  static auto RunPrompt() -> void;
  static auto Run(std::string source) -> void;
  static auto Report(int line, std::string_view where, std::string_view message)
      -> void;
};

#endif  // LOX_LOX_H
