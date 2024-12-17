
#include "main.hpp"

int main() {
  std::vector<std::string> flags;
  std::vector<std::string> patterns;

  loadData("./input", flags, patterns);

  std::cout << "Flags: " << flags.size() << std::endl;
  std::cout << "Patterns: " << patterns.size() << std::endl;
  uint64_t result = 0;
  for (const auto &pattern : patterns) {
    result += countWaysToMakeWord(pattern, flags);
  }
  std::cout << "Result: " << result << std::endl;
  return 0;
}

// Load map from file
void loadData(const std::string &filename, std::vector<std::string> &flags,
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
    flags.push_back(line);
  }
  patterns.reserve(1000);
  while (std::getline(inputFS, line)) {
    patterns.push_back(line);
  }
  inputFS.close();
}

uint64_t countWaysToMakeWord(const std::string &word,
                             const std::vector<std::string> &tokens) {
  int n = word.size();
  std::vector<uint64_t> dp(n + 1, 0);
  dp[0] = 1;  

  for (int i = 1; i <= n; ++i) {
    for (const auto &token : tokens) {
      int len = token.size();
      if (i >= len && word.substr(i - len, len) == token) {
        dp[i] += dp[i - len];
      }
    }
  }

  return dp[n];
}