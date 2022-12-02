#ifndef LOX_SRC_UTIL_STRING_UTIL_H_
#define LOX_SRC_UTIL_STRING_UTIL_H_

#include <algorithm>
#include <memory>
#include <string>

class StringUtil {
 public:
  // trim functions from: https://stackoverflow.com/a/217605
  // trim from start (in place)
  static inline void LTrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char c) {
              return !std::isspace(c);
            }));
  }

  // trim from end (in place)
  static inline void RTrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](unsigned char c) { return !std::isspace(c); })
                .base(),
            s.end());
  }

  // trim from both ends (in place)
  static inline void Trim(std::string& s) {
    LTrim(s);
    RTrim(s);
  }

  static auto Tokenize(const std::string& s, const char delim = ',')
      -> std::vector<std::string> {
    auto tokens = std::vector<std::string>{};
    auto str = std::string(s);

    while (!str.empty()) {
      auto idx = str.find(delim);
      if (idx != std::string::npos) {
        tokens.emplace_back(str.substr(0, idx));
        str = str.substr(idx + 1);
      } else {
        tokens.emplace_back(str);
        str = "";
      }
    }

    return tokens;
  }
};

#endif  // LOX_SRC_UTIL_STRING_UTIL_H_
