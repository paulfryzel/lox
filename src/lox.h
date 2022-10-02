#ifndef LOX_LOX_H
#define LOX_LOX_H

#include <string>
#include <string_view>
#include <vector>

class Lox {
 public:
  static void Main(const std::vector<std::string>& args);
  static void Error(int line, std::string_view message);

  static bool had_error_;

 private:
  static void RunFile(const std::string& filename);
  static void RunPrompt();
  static void Run(const std::string& source);
  static void Report(int line, std::string_view where,
                     std::string_view message);
};

#endif  // LOX_LOX_H
