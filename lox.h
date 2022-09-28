#ifndef LOX_LOX_H
#define LOX_LOX_H

#include <string>
#include <string_view>
#include <vector>

class Lox {
 public:
  static void main(std::vector<std::string> &args);
  static void error(int line, std::string_view message);

  static bool had_error_;

 private:
  static void run_file(const std::string &filename);
  static void run_prompt();
  static void run(std::string_view source);
  static void report(int line,
                     std::string_view where,
                     std::string_view message);
};

#endif //LOX_LOX_H
