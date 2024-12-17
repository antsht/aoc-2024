
#include "main.hpp"

int main() {
  std::set<std::string> flags;
  std::vector<std::string> patterns;

  loadData("./input_s", flags, patterns);

  std::cout << "Flags: " << flags.size() << std::endl;
  std::cout << "Patterns: " << patterns.size() << std::endl;

  int possible_patterns = 0;
  for (const auto &pattern : patterns) {

    bool full_match = false;
    std::cout << "Pattern: " << pattern << std::endl;
    std::cout << "Pattern size: " << pattern.size() << std::endl;
    std::set<std::string> pattern_remains{pattern};
    while (pattern_remains.size() > 0) {
      std::set<std::string> new_remains{};
      for (const auto &pattern_curr : pattern_remains) {
        for (const auto &flag : flags) {
          int index = pattern_curr.find(flag);
          if (index == 0) {
            std::string pattern_trimmed = pattern_curr.substr(index + flag.size());
            std::cout << "Flag: " << flag
                      << ", Pattern trimmed: " << pattern_trimmed << std::endl;
            if (pattern_trimmed.size() == 0) {
              full_match = true;
              break;
            }
            if (pattern_trimmed.size() < pattern.size()) {
              new_remains.insert(pattern_trimmed);
            }
          }
        }
        if (full_match) {
          break;
        }
      }
      std::cout << "New remains size: " << new_remains.size() << std::endl;
      if (full_match) {
        possible_patterns++;
        break;
      }
      if (pattern_remains== new_remains) {
        break;
      }
      pattern_remains = new_remains;
    }
    std::cout << "Full match: " << full_match << std::endl;
  }

  std::cout << "Possible patterns: " << possible_patterns << std::endl;
  return 0;
}

// Load map from file
void loadData(const std::string &filename, std::set<std::string> &flags,
              std::vector<std::string> &patterns) {
  std::ifstream inputFS(filename);
  if (!inputFS.is_open()) {
    throw std::runtime_error("Error: Unable to open input file.");
  }

  std::string line;
  while (std::getline(inputFS, line)) {
    if (line.empty()) {
      break;
    }
    flags.insert(line);
  }
  patterns.reserve(1000);
  while (std::getline(inputFS, line)) {
    patterns.push_back(line);
  }
  inputFS.close();
}
