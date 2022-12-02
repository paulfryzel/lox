#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "util/string_util.h"

void DefineType(std::ofstream& out, const std::string& base_name,
                const std::string& class_name, const std::string& field_list) {
  out << "class " + class_name + " : " + base_name + " {\n";
  out << "  " + class_name + '(' + field_list + ") {}\n";
  out << "};\n\n";
}

void DefineAst(const std::string& output_dir, const std::string& base_name,
               const std::vector<std::string>& types) {
  std::string path = output_dir + '/' + base_name + ".cpp";

  std::ofstream out(path, std::ios::out);
  if (out) {
    out << "#include <vector>\n";
    out << '\n';
    out << "struct " + base_name + " {\n";
    out << "};\n";
    out << '\n';

    for (const auto& type : types) {
      auto colon_idx = type.find(':');
      std::string class_name = type.substr(0, colon_idx);
      StringUtil::Trim(class_name);
      std::string fields = type.substr(colon_idx + 1);
      StringUtil::Trim(fields);
      DefineType(out, base_name, class_name, fields);
    }
    out.close();
  }
}

auto main(int argc, char** argv) -> int {
  if (argc != 2) {
    std::cerr << "Usage: generate_ast <output directory>" << '\n';
    return 64;
  }
  auto output_dir = argv[1];

  std::vector<std::string> types = {
      "Binary   : Expr left, Token operator, Expr right",
      "Grouping : Expr expression", "Literal  : Object value",
      "Unary    : Token operator, Expr right"};
  DefineAst(output_dir, "Expr", types);

  return 0;
}
