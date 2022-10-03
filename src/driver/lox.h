#ifndef LOX_LOX_H
#define LOX_LOX_H

#include <string>
#include <vector>

class Lox {
 public:
  static void Main(const std::vector<std::string>& args);
  static void Error(int line, const std::string& message);

  static bool had_error;

 private:
  static void RunFile(const std::string& filename);
  static void RunPrompt();
  static void Run(const std::string& source);
  static void Report(int line, const std::string& where,
                     const std::string& message);
};

#endif  // LOX_LOX_H
