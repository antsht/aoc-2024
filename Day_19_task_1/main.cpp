
#include "main.hpp"

int main() {
  std::set<std::string> flags;
  std::vector<std::string> patterns;

  loadData("./input_test_s", flags, patterns);

  std::cout << "Flags: " << flags.size() << std::endl;
  std::cout << "Patterns: " << patterns.size() << std::endl;
  for (const auto &pattern : patterns) {
    std::cout << pattern << std::endl;

  }


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
